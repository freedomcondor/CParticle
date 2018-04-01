luaPath_src = ';../src/'
luaExt = '?.lua'
package.path = package.path .. luaPath_src .. "Lua/" .. luaExt
--local State = require("State")
local Vec3 = require("Vector3")

--[[
  global:
  	box: functions
	sensor
	beingcarried = true/false
	selfstig
--]]

local ROBOT = 0
local BOX = 1
local WALL = 2

local FRONT = 1
local LEFT = 2
local UP = 3
local DOWN = 4
local RIGHT = 5
local BACK = 6

local boxsize = 0.1

function vec2stig(x)
	local l = Vec3:create(x.x,x.y,x.z)
	if (l - Vec3:create(1,0,0)*boxsize):len() < boxsize / 2 then
		return FRONT
	else if (l - Vec3:create(-1,0,0)*boxsize):len() < boxsize / 2 then
		return BACK
	else if (l - Vec3:create(0,1,0)*boxsize):len() < boxsize / 2 then
		return LEFT
	else if (l - Vec3:create(0,-1,0)*boxsize):len() < boxsize / 2 then
		return RIGHT
	else if (l - Vec3:create(0,0,1)*boxsize):len() < boxsize / 2 then
		return UP
	else if (l - Vec3:create(0,0,-1)*boxsize):len() < boxsize / 2 then
		return DOWN
	end end end end end end
end
function stig2vec(x)
	if x == FRONT then
		return Vec3:create(1,0,0) * boxsize
	else if x == END then
		return -Vec3:create(1,0,0) * boxsize
	else if x == UP then
		return Vec3:create(0,0,1) * boxsize
	else if x == DOWN then
		return -Vec3:create(0,0,1) * boxsize
	else if x == LEFT then
		return Vec3:create(0,1,0) * boxsize
	else if x == RIGHT then
		return -Vec3:create(0,1,0) * boxsize
	end end end end end end
end

local getStigVector = function(x,_dF,_dU)
	-- x == 1 ~ 6 which is FRONT/BACK/...
	local dF = Vec3:create(_dF.x,_dF.y,_dF.z)
	local dU = Vec3:create(_dU.x,_dU.y,_dU.z)
	if x == FRONT then
		return dF:nor() * boxsize
	else if x == BACK then
		return -dF:nor() * boxsize
	else if x == UP then
		return dU:nor() * boxsize
	else if x == DOWN then
		return -dU:nor() * boxsize
	else if x == LEFT then
		return (dU * dF):nor() * boxsize
	else if x == RIGHT then
		return (dF * dU):nor() * boxsize
	end end end end end end
end

function init()
	--print("box lua init",box)
end

function step()
	if beingcarried == true then
		return nil
	end
	if fixed == false then
		return nil
	end

	-- clear my own stig
	for i = 1, sensor.n do
		if sensor[i].type == BOX then
			local l = Vec3:create(sensor[i].l.x,sensor[i].l.y,sensor[i].l.z)
			for j = 1, 6 do
				if selfstig[j] == true and
				   (l - stig2vec(j)):len() < boxsize / 2 then
				   	print("a stig unset")
				    box:unsetstig(j)
				end
			end
		end
	end

	-- inhert others stig
	for i = 1, sensor.n do
		if sensor[i].type == BOX then
			for j = 1, 6 do
				if sensor[i].fixed == true and sensor[i].stig[j] == true then
					local l = Vec3:create(sensor[i].l.x,sensor[i].l.y,sensor[i].l.z)
				   	if (getStigVector(j,sensor[i].dF,sensor[i].dU) + l):len() < boxsize / 2 then
				   		print("i have an inhert")
						local st = vec2stig(sensor[i].l)
						box:setstig(7 - st)
				   	end
				end
			end
		end
	end

	--[[
	print("---------------------------------")
	print("selfstig",selfstig.n)
	for i = 1, 6 do
		print("selfstig",selfstig[i])
	end
	--]]
end

function destroy()
	--print("box lua destroy")
end
