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
	print("something impossible: you ask for a vec other than six direction:",x)
end
function stig2vec(x)
	if x == FRONT then
		return Vec3:create(1,0,0) * boxsize
	else if x == BACK then
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
	print("something impossible: you ask for a stig other than six direction:",x)
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

	-- perception, see whos in my FRONT/BACK/LEFT..
	local perception = {}
	for i = 1, sensor.n do
		local l = Vec3:create(sensor[i].l.x,sensor[i].l.y,sensor[i].l.z)
		sensor[i].l = l
		for j = 1, 6 do
			if sensor[i].type == BOX and
			   sensor[i].fixed == true and
			   (l - stig2vec(j)):len() < boxsize / 2 then
				perception[j] = sensor[i]
			end
		end
	end

	-- clear my own stig
	local stigflag = 0
	for j = 1, 6 do
		if selfstig[j] ~= 0 and perception[j] ~= nil then
			stigflag = 1
			box:unsetstig(j)
			selfstig.n = selfstig.n - 1
		end
	end

	-- currently someting wrong
	print("selfstig.n",selfstig.n)
	if stigflag == 1 and selfstig.n == 0 then
		print("i am full")
		box:unsetfix()
	end

	-- inhert others stig
	for i = 1, 6 do
		if perception[i] ~= nil then
			for j = 1, 6 do
				if perception[i].stig[j] ~= 0 and 
				   (getStigVector(j,perception[i].dF,perception[i].dU) + perception[i].l):len() < boxsize / 2 then
					--print("i have an inhert")
					local st = vec2stig(perception[i].l)
					box:setstig(7 - st)
					if st == FRONT or st == BACK then to = LEFT end
					if st == LEFT or st == RIGHT then to = FRONT end
					if perception[to] == nil then box:setstig(to) end
					if perception[7-to] == nil then box:setstig(7 - to) end
				end
			end
		end
	end
	--[[
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
	--]]
end

function destroy()
	--print("box lua destroy")
end
