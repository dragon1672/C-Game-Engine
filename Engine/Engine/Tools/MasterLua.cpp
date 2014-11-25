#include "MasterLua.h"
#include <string>
#include <iostream>
#include <Engine/Tools/Printer.h>

//singletons
#include <Engine/Tools/Timer.h>
#include <engine/Tools/Random/MyRandom.h>
#include <Engine/Tools/Random/StringRandom.h>
#include <Engine/Systems/InputManager.h>
#include <Engine/Systems/GameObjectManager.h>

const std::string MasterLua::ComponentBaseClass = "ScriptComponent";
IMPLEMENT_SINGLETON(MasterLua);



/* documentation

-- generic vector
BaseVector

--abstract functions
--returns vector size
Size()
--returns part of vector
--1 -> x, 2->y, etc
Get(index)
--set value (see get for indexes)
Set(index,val)
--creates a copy of values in a new vector
Clone()


--compares vectors
function BaseVector:isEqual(that)
-- returns { x,y,z }
function BaseVector:toString()

--used internally, apply operator to each element in vector
--that: (vector) 
--operator: (function) takes 2 numbers
function BaseVector:ApplyOperator(that,operator)

-- adds vectors and returns new vector instance
-- that:(vector)
-- {1,2} + {2,1} = {3,3}
function BaseVector:add(that)

-- subtracts vectors and returns new vector instance
-- that:(vector)
-- {1,2} - {2,1} = {-1,1}
function BaseVector:sub(that)

-- multiply vectors and returns new vector instance
-- if vector is passed
--     each element is multiplied with corresponding element in vector
--     {3,4} * {2,3} = {6,12}
--if number is passed
--   each element is multiplied by number, new instance is returned
--   {3,4} * 2 = {6,8}
function BaseVector:mul(thatOrConst)

-- divides vector by number
-- content(number)
function BaseVector:div(content)

--returns dot product
-- that(vector)
function BaseVector:dot(that)

--returns the length of this vector squared (very cheap operation)
function BaseVector:lengthSquared()

--returns the length of vector (uses square root, not as cheap as length squared)
function BaseVector:length()

--returns a new vector with length of one (still same direction as current)
function BaseVector:normalized()
function BaseVector:LERP(percent, that)
function BaseVector:projection(norm)
function BaseVector:rejection(norm)
function BaseVector:isZero()



--returns new vector rotated 90 degrees
function Vector2:perpCW()
--returns new vector rotated -90 degrees
function Vector2:perpCCW()
--returns new vector that is cross product between this and that(vector)
function Vector2:cross(that)

--returns boolean if within 0,0 and box
-- {5,5}.withinBox({10,10}) -- true
-- {-5,-5}.withinBox({10,10}) -- false
-- {10,10}.withinBox({10,10}) -- false
-- {10,10}.withinBox({-1,-1}) -- badly formed box
function Vector2:withinBox(exclusiveBounds)



//*/

MasterLua::MasterLua()
{
	lua.LoadStandardLibraries();

	lua.GetGlobalEnvironment().Set("print",lua.CreateFunction<void(std::string)>([](std::string a) -> void { std::cout << "LUA Print:" << a << std::endl; })); // make and add function

	//load class def
	lua.RunScript("function class(a,b)local c={}if not b and type(a)=='function'then b=a;a=nil elseif type(a)=='table'then for d,e in pairs(a)do c[d]=e end;c._base=a end;"
		"c.__index=c;local f={}f.__call=function(g,...)local h={}setmetatable(h,c)if b then b(h,...)else if a and a.init then a.init(h,...)end end;return h end;c.init=b;"
		"c.is_a=function(i,j)local k=getmetatable(i)while k do if k==j then return true end;k=k._base end;return false end;setmetatable(c,f)return c end");
	lua.RunScript("function between(num, min,max) return min <= num and num <= max; end");
	lua.RunScript(ComponentBaseClass+" = class();"
		//setting up defaults for functions
		"function "+ComponentBaseClass+":init()        return true end \n"
		"function "+ComponentBaseClass+":start()       return true end \n"
		"function "+ComponentBaseClass+":earlyUpdate() return true end \n"
		"function "+ComponentBaseClass+":update()      return true end \n"
		"function "+ComponentBaseClass+":lateUpdate()  return true end \n"
		"");

#pragma region setting up vector lib
	lua.RunScript(""
		"BaseVector = class()                                                                                                                                      \n"
		" --abstract methods                                                                                                                                       \n"
		"function BaseVector:Size()                                                                                                                                \n"
		"  return -1                                                                                                                                               \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:Get(index)                                                                                                                            \n"
		"  return nil;                                                                                                                                             \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:Set(index,val)                                                                                                                        \n"
		"                                                                                                                                                          \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:Clone()                                                                                                                               \n"
		"  return nil                                                                                                                                              \n"
		"end                                                                                                                                                       \n"
		"                                                                                                                                                          \n"
		"--basic methods                                                                                                                                           \n"
		"function BaseVector:isEqual(that)                                                                                                                         \n"
		"  assert(type(that)=='table' and that:is_a(BaseVector) and that:Size() == self:Size());                                                                   \n"
		"  for i=1,self:Size() do                                                                                                                                  \n"
		"    if(self:Get(i) ~= that:Get(i)) then return false; end                                                                                                 \n"
		"  end                                                                                                                                                     \n"
		"  return true;                                                                                                                                            \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:toString()                                                                                                                            \n"
		"  local ret = '{ '                                                                                                                                        \n"
		"  local dim = '';                                                                                                                                         \n"
		"  for i=1,self:Size() do                                                                                                                                  \n"
		"    ret = ret .. dim .. self:Get(i);                                                                                                                      \n"
		"    dim = ', ';                                                                                                                                           \n"
		"  end                                                                                                                                                     \n"
		"  return ret ..' }';                                                                                                                                      \n"
		"end                                                                                                                                                       \n"
		"                                                                                                                                                          \n"
		"                                                                                                                                                          \n"
		"function BaseVector:ApplyOperator(that,operator)                                                                                                          \n"
		"  assert(type(that)=='table' and that:is_a(BaseVector) and that:Size() == self:Size());                                                                   \n"
		"  local ret = self:Clone();                                                                                                                               \n"
		"  for i=1,self:Size() do                                                                                                                                  \n"
		"    ret:Set(i,operator(self:Get(i),that:Get(i)));                                                                                                         \n"
		"  end                                                                                                                                                     \n"
		"  return ret;                                                                                                                                             \n"
		"end                                                                                                                                                       \n"
		"                                                                                                                                                          \n"
		"function BaseVector:add(that) return self:ApplyOperator(that,function(left,right) return left + right; end); end                                          \n"
		"function BaseVector:sub(that) return self:ApplyOperator(that,function(left,right) return left - right; end); end                                          \n"
		"function BaseVector:mul(thatOrConst)                                                                                                                      \n"
		"  local ret = self:Clone();                                                                                                                               \n"
		"  if(type(thatOrConst) == 'number') then                                                                                                                  \n"
		"    for i=1,self:Size() do                                                                                                                                \n"
		"      ret.Set(i,self:Get(i) * thatOrConst);                                                                                                               \n"
		"    end                                                                                                                                                   \n"
		"  elseif(type(thatOrConst)=='table') then                                                                                                                 \n"
		"    for i=1,self:Size() do                                                                                                                                \n"
		"      ret.Set(i,self:Get(i) * thatOrConst:Get(i));                                                                                                        \n"
		"    end                                                                                                                                                   \n"
		"  else                                                                                                                                                    \n"
		"    assert(false);                                                                                                                                        \n"
		"  end                                                                                                                                                     \n"
		"  return ret;                                                                                                                                             \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:div(constent)                                                                                                                         \n"
		"  return self:mul(1/constent);                                                                                                                            \n"
		"  end                                                                                                                                                     \n"
		"function BaseVector:dot(that)                                                                                                                             \n"
		"  assert(type(that)=='table' and that:is_a(BaseVector) and that:Size() == self:Size());                                                                   \n"
		"  local ret = 0;                                                                                                                                          \n"
		"  for i=1,self:Size() do                                                                                                                                  \n"
		"    ret = ret + self:Get(i) * that:Get(i);                                                                                                                \n"
		"  end                                                                                                                                                     \n"
		"  return ret;                                                                                                                                             \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:lengthSquared()                                                                                                                       \n"
		"  return self:dot(self);                                                                                                                                  \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:length()                                                                                                                              \n"
		"  return math.sqrt(self:lengthSquared(self));                                                                                                             \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:normalized()                                                                                                                          \n"
		"  return self:div(math.sqrt(self:lengthSquared(self)));                                                                                                   \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:LERP(percent, that)                                                                                                                   \n"
		"  assert(type(percent)=='number' and type(that)=='table' and that:is_a(BaseVector) and that:Size() == self:Size());                                       \n"
		"  return self:mul(1-percent):add(that:mul(percent));                                                                                                      \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:projection(norm)                                                                                                                      \n"
		"  return norm:mul(self:dot(norm)):div(norm:lengthSquared());                                                                                              \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:rejection(norm)                                                                                                                       \n"
		"  return self:sub(self:projection(norm));                                                                                                                 \n"
		"end                                                                                                                                                       \n"
		"function BaseVector:isZero()                                                                                                                              \n"
		"  for i=1,self:Size() do                                                                                                                                  \n"
		"    if(self:Get(i) ~= 0) then return false; end                                                                                                           \n"
		"  end                                                                                                                                                     \n"
		"end                                                                                                                                                       \n"
		"                                                                                                                                                          \n"
		"                                                                                                                                                          \n"
		"                                                                                                                                                          \n"
		"Vector2 = class(BaseVector,function(self,x,y)                                                                                                             \n"
		"    if(type(x)=='table' and x:is_a(BaseVector)) then                                                                                                      \n"
		"      assert(y==nil);                                                                                                                                     \n"
		"      self.x = x.x;                                                                                                                                       \n"
		"      self.y = x.y;                                                                                                                                       \n"
		"    else                                                                                                                                                  \n"
		"      assert(type(x)=='number' and type(y)=='number');                                                                                                    \n"
		"      self.x = x or 0;                                                                                                                                    \n"
		"      self.y = y or 0;                                                                                                                                    \n"
		"    end                                                                                                                                                   \n"
		"  end)                                                                                                                                                    \n"
		"function Vector2:Get(index)                                                                                                                               \n"
		"  if(index==1) then return self.x; end                                                                                                                    \n"
		"  if(index==2) then return self.y; end                                                                                                                    \n"
		"  return nil;                                                                                                                                             \n"
		"end                                                                                                                                                       \n"
		"function Vector2:Set(index,val)                                                                                                                           \n"
		"  if(index==1) then self.x = val; end                                                                                                                     \n"
		"  if(index==2) then self.y = val; end                                                                                                                     \n"
		"  return nil;                                                                                                                                             \n"
		"end                                                                                                                                                       \n"
		"function Vector2:Size() return 2 end                                                                                                                      \n"
		"function Vector2:Clone()                                                                                                                                  \n"
		"  return Vector2(x,y);                                                                                                                                    \n"
		"end                                                                                                                                                       \n"
		"function Vector2:perpCW()                   return Vector2(-self.y,self.x);                      end                                                      \n"
		"function Vector2:perpCCW()                  return Vector2(self.y,-self.x);                      end                                                      \n"
		"function Vector2:cross(that)                return self.x * that.y - self.y * that.x;            end                                                      \n"
		"function Vector2:withinBox(exclusiveBounds) return self.x >= 0 and self.y >= 0 and self.x < exclusiveBounds.x and self.y < exclusiveBounds.y; end         \n"
		"                                                                                                                                                          \n"
		"Vector3 = class(BaseVector,function(self,x,y,z)                                                                                                           \n"
		"    if(type(x)=='table' and x:is_a(Vector2)) then                                                                                                         \n"
		"      assert(type(y)=='number' and z==nil);                                                                                                               \n"
		"      self.x = x.x;                                                                                                                                       \n"
		"      self.y = x.y;                                                                                                                                       \n"
		"      self.z = y;                                                                                                                                         \n"
		"    elseif(type(x)=='table' and x:is_a(BaseVector)) then --truncates larger vectors                                                                       \n"
		"      assert(y==nil and z==nil);                                                                                                                          \n"
		"      self.x = x.x;                                                                                                                                       \n"
		"      self.y = x.y;                                                                                                                                       \n"
		"      self.z = x.z;                                                                                                                                       \n"
		"    else                                                                                                                                                  \n"
		"      assert(type(x)=='number' or x == nil and type(y)=='number' or y == nil and type(z)=='number' or z == nil);                                          \n"
		"      self.x = x or 0;                                                                                                                                    \n"
		"      self.y = y or 0;                                                                                                                                    \n"
		"      self.z = z or 0;                                                                                                                                    \n"
		"    end                                                                                                                                                   \n"
		"  end)                                                                                                                                                    \n"
		"function Vector3:Get(index)                                                                                                                               \n"
		"  if(index==1) then return self.x; end                                                                                                                    \n"
		"  if(index==2) then return self.y; end                                                                                                                    \n"
		"  if(index==3) then return self.z; end                                                                                                                    \n"
		"  return nil;                                                                                                                                             \n"
		"end                                                                                                                                                       \n"
		"function Vector3:Set(index,val)                                                                                                                           \n"
		"  if(index==1) then self.x = val; end                                                                                                                     \n"
		"  if(index==2) then self.y = val; end                                                                                                                     \n"
		"  if(index==3) then self.z = val; end                                                                                                                     \n"
		"  return nil;                                                                                                                                             \n"
		"end                                                                                                                                                       \n"
		"function Vector3:Size() return 3 end                                                                                                                      \n"
		"function Vector3:Clone()                                                                                                                                  \n"
		"  return Vector3(x,y,z);                                                                                                                                  \n"
		"end                                                                                                                                                       \n"
		"");
#pragma endregion

#pragma region setting up matrix lib
	lua.RunScript(""
		"MatrixBase = class(function(self,size)                                                       \n"
		"    self._dim = 3;                                                                           \n"
		"    self.matrix = {};                                                                        \n"
		"    for i=1,self._dim do                                                                     \n"
		"      self.matrix[i] = {}                                                                    \n"
		"      for j=1,self._dim do                                                                   \n"
		"          if(i==j) then                                                                      \n"
		"            self.matrix[i][j] = 1;                                                           \n"
		"          else                                                                               \n"
		"            self.matrix[i][j] = 0;                                                           \n"
		"          end                                                                                \n"
		"        end                                                                                  \n"
		"    end                                                                                      \n"
		"  end)                                                                                       \n"
		"function MatrixBase:size() return self._dim end                                              \n"
		"                                                                                             \n"
		"                                                                                             \n"
		"Matrix3 = class(function(self,m11,m21,m31,m12,m22,m32,m13,m23,m33)                           \n"
		"    MatrixBase.init(self,3);                                                                 \n"
		"    if(m11) then                                                                             \n"
		"      if(type(m11) == 'number') then                                                         \n"
		"        self.matrix[1][1] = m11; self.matrix[2][1] = m21; self.matrix[3][1] = m31;           \n"
		"        self.matrix[1][2] = m12; self.matrix[2][2] = m22; self.matrix[3][2] = m32;           \n"
		"        self.matrix[1][3] = m13; self.matrix[2][3] = m23; self.matrix[3][3] = m33;           \n"
		"      elseif(type(m11)=='table' and m11:is_a(Vector3)) then                                  \n"
		"        self:setCol(1,m11);                                                                  \n"
		"        self:setCol(2,m21);                                                                  \n"
		"        self:setCol(3,m31);                                                                  \n"
		"      else                                                                                   \n"
		"        assert(false)                                                                        \n"
		"      end                                                                                    \n"
		"    end                                                                                      \n"
		"                                                                                             \n"
		"  end);                                                                                      \n"
		"                                                                                             \n"
		"function Matrix3:getRow(i)                                                                   \n"
		"  assert(type(i)=='number');                                                                 \n"
		"  return Vector3(self.matrix[1][i],self.matrix[2][i],self.matrix[3][i]);                     \n"
		"end                                                                                          \n"
		"function Matrix3:setRow(row, vec)                                                            \n"
		"  assert(type(row) == 'number' and type(vec)=='table' and vec:is_a(Vector3));                \n"
		"  for i=1,self:size() do                                                                     \n"
		"    self.matrix[i][row] = vec:Get(i);                                                        \n"
		"  end                                                                                        \n"
		"end                                                                                          \n"
		"function Matrix3:getCol(i)                                                                   \n"
		"  assert(type(i)=='number');                                                                 \n"
		"  return Vector3(self.matrix[i][1],self.matrix[i][2],self.matrix[i][3]);                     \n"
		"end                                                                                          \n"
		"function Matrix3:setCol(col, vec)                                                            \n"
		"  assert(type(col) == 'number' and type(vec)=='table' and vec:is_a(Vector3));                \n"
		"  for i=1,self:size() do                                                                     \n"
		"    self.matrix[col][row] = vec:Get(i);                                                      \n"
		"  end                                                                                        \n"
		"end                                                                                          \n"
		"                                                                                             \n"
		"function Matrix3:mul(that)                                                                   \n"
		"  assert(type(that)=='table');                                                               \n"
		"  if(that:is_a(Matrix3)) then                                                                \n"
		"                                                                                             \n"
		"  elseif(that:is_a(Vector3)) then                                                            \n"
		"    local ret = Vector3();                                                                   \n"
		"    for i=1, 3 do                                                                            \n"
		"      ret:Set(i,self:getRow(i):dot(that));                                                   \n"
		"    end                                                                                      \n"
		"    return ret;                                                                              \n"
		"  elseif(that:is_a(Vector2)) then                                                            \n"
		"    local ret = Vector3();                                                                   \n"
		"    local vecAs3 = Vector3(that,1);                                                          \n"
		"    for i=1, 3 do                                                                            \n"
		"      ret:Set(i,self:getRow(i).dot(vecAs3));                                                 \n"
		"    end                                                                                      \n"
		"    return Vector2(ret);                                                                     \n"
		"  else                                                                                       \n"
		"    assert(false);                                                                           \n"
		"  end                                                                                        \n"
		"end                                                                                          \n"
		"");
#pragma endregion

#pragma region setting up binding

	lua.RunScript(""
		"--converts between Engine Vector and LUA vector             \n"
		"function setVector3(GameEngineVectorToSet,vec)              \n"
		"  GameEngineVectorToSet.setX(vec.Get(1));                   \n"
		"  GameEngineVectorToSet.setY(vec.Get(2));                   \n"
		"  GameEngineVectorToSet.setZ(vec.Get(3));                   \n"
		"end                                                         \n"
		"function setVector2(GameEngineVectorToSet,vec)              \n"
		"  GameEngineVectorToSet.setX(vec.Get(1));                   \n"
		"  GameEngineVectorToSet.setY(vec.Get(2));                   \n"
		"end                                                         \n"
		"function getVector3(GameEngineVectorToGet)                  \n"
		"  local x = GameEngineVectorToGet.getX();                   \n"
		"  local y = GameEngineVectorToGet.getY();                   \n"
		"  local z = GameEngineVectorToGet.getZ();                   \n"
		"  return Vector3(x,y,z);                                    \n"
		"end                                                         \n"
		"function getVector2(GameEngineVectorToGet)                  \n"
		"  local x = GameEngineVectorToGet.getX();                   \n"
		"  local y = GameEngineVectorToGet.getY();                   \n"
		"  return Vector2(x,y);                                      \n"
		"end                                                         \n"
		"");
#pragma endregion

#pragma region default collections

	lua.RunScript(""
		"--List is a collection that allows push,pop,get,and set             \n"
		"List = class(function(self)                                         \n"
		"    self.size = 0;                                                  \n"
		"    self._table = {};                                               \n"
		"  end)                                                              \n"
		"--returns the item at the given index                               \n"
		"--there is no current check for bounds                              \n"
		"function List:get(index)                                            \n"
		"  return self._table[index];                                        \n"
		"end                                                                 \n"
		"--adds given item to the end of the list                            \n"
		"function List:push(var)                                             \n"
		"  self.size = self.size + 1;                                        \n"
		"  self._table[self.size] = var;                                     \n"
		"end                                                                 \n"
		"--returns the number of elements in the list                        \n"
		"function List:getSize()                                             \n"
		"  return self.size;                                                 \n"
		"end                                                                 \n"
		"--removes the given index and shuffles other entries back one       \n"
		"function List:remove(index)                                         \n"
		"  for i=index,self.size do                                          \n"
		"    self._table[i] = self._table[i+1];                              \n"
		"  end                                                               \n"
		"  self:popBack();                                                   \n"
		"end                                                                 \n"
		"--removes the last element and returns it                           \n"
		"function List:popBack()                                             \n"
		"  self.size = self.size-1;                                          \n"
		"  return self._table[self.size+1];                                  \n"
		"end                                                                 \n"
		"");

#pragma endregion

	//random
	auto rand = lua.CreateTable();

	rand.Set("float",     lua.CreateFunction<float()>([]() { return Random::Float(); }));
	rand.Set("bool",      lua.CreateFunction<bool()>([]() { return Random::Bool(); }));
	rand.Set("RangeFloat",lua.CreateFunction<float(float,float)>([](float low, float high) { return Random::Float(low,high); }));
	rand.Set("RangeInt",  lua.CreateFunction<int(int,int)>([](int low, int high) { return Random::Int(low,high); }));
	LuaTable randStr = lua.CreateTable();
	rand.Set("String",    randStr);
	randStr.Set("String",    lua.CreateFunction<std::string(int,int,int)>([](int len, int start, int end) { return Random::rString::makeString(len, start, end); }));
	randStr.Set("Letters",   lua.CreateFunction<std::string(int)>([](int len) { return Random::rString::Letters(len); }));
	randStr.Set("UppercaseLetters",   lua.CreateFunction<std::string(int)>([](int len) { return Random::rString::UppercaseLetters(len); }));
	randStr.Set("LowercaseLetters",   lua.CreateFunction<std::string(int)>([](int len) { return Random::rString::LowercaseLetters(len); }));
	lua.GetGlobalEnvironment().Set("Random",rand);


	auto KeyCodes = lua.CreateTable();
	for (int i = KeyCode::A; i < KeyCode::Z; i++) KeyCodes.Set(std::string(1,(char)i),i);
	std::string kodes[] = { "ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE" };
	for (int i = KeyCode::ZERO; i < KeyCode::NINE; i++) KeyCodes.Set(kodes[i-KeyCode::ZERO],i);
	KeyCodes.Set("SHIFT",(int)KeyCode::SHIFT);
	lua.GetGlobalEnvironment().Set("KeyCode",KeyCodes);


	auto mCodes = lua.CreateTable();
	mCodes.Set("LEFT_MOUSE",  (int)MouseCodes::LEFT_MOUSE  );
	mCodes.Set("RIGHT_MOUSE", (int)MouseCodes::RIGHT_MOUSE );
	mCodes.Set("MIDDLE_MOUSE",(int)MouseCodes::MIDDLE_MOUSE);
	lua.GetGlobalEnvironment().Set("MouseCodes",mCodes);

}

void MasterLua::init()
{
	//register all singletons here
	auto global = lua.GetGlobalEnvironment();
	global.Set("Timer",(LuaUserdata<Timer>)Timer::getInstance());
	global.Set("Input",(LuaUserdata<InputManager>)InputManager::getInstance());
	global.Set("GameManager",(LuaUserdata<GameObjectManager>)GameObjectManager::getInstance());
}

void MasterLua::runLua(std::string toRun)
{
	std::string errs = LUA_INSTANCE.RunScript(toRun);
	if(errs != Lua::NO_ERRORS) {
		printer.LogError("LUA COMPILE ERR");
		printer.LogError(errs.c_str());
	}
}
