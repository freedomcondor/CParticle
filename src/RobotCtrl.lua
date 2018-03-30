luaPath_src = ';../src/'
luaExt = '?.lua'
package.path = package.path .. luaPath_src .. "Lua/" .. luaExt
local State = require("State")
local Vec3 = require("Vector3")

--[[
 global varible:
 	robot:	setspeed(x)
			setturn
			setarm
			tocarry

	sensor.n
	sensor[i] = {
		l,dF,dU
		type = 0/1/2  (ROBOT/BOX/WALL)
		obj = pointer to the in C++
		if a box:
		size
		fixed = true/false
		if fixed == true
		stig = {n,1,2,3,4,5,6}
			stig[1] = true or false
	}
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

local frontcheck = function(sig)
	if sig.l.x > 0 then
		return true
	else
		return false
	end
end

local getStigVector = function(x,_dF,_dU)
	-- x == 1 ~ 6 which is FRONT/BACK/...
	dF = Vec3:create(_dF.x,_dF.y,_dF.z)
	dU = Vec3:create(_dU.x,_dU.y,_dU.z)
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

local movestate = State:create
{
	id = "RobotController",
	data = {turncount = 0,
			armcount = 0,
			armspeed = 90 * 10,
			unloadsig = nil,
			turnbackflag = 0;
	},
	substates = {
		random = {method = 
			function(_currentstate,father) 
				for i = 1, sensor.n do
					if frontcheck(sensor[i]) == true and sensor[i].type == ROBOT then	-- 0 box
						--return "turnback"
					end
					if frontcheck(sensor[i]) == true and 
					   sensor[i].type == BOX and sensor[i].beingcarried == false then	-- 1 box
						if carrying == false and sensor[i].fixed == false then	-- if can carry
							--print("carry");
							robot:tocarry(sensor[i].obj)
							return "armup"
						else if carrying == false and sensor[i].fixed == true then
							-- just go away
							return "turnback"
						else if carrying == true and sensor[i].fixed == true then
							print("-------------stig",sensor[i].stig.n)
							-- see if I can unload
							for j = 1, 6 do
								if sensor[i].stig[j] == true then
									print("-----------stig",j)
									local usig = sensor[i]
									local stigvec = getStigVector(j,usig.dF,usig.dU)
									if stigvec.x < 0 then	-- unload direction check
										usig.l = Vec3:create(usig.l.x,usig.l.y,usig.l.z)
										usig.l = usig.l + stigvec 
										father.data.unloadsig = usig
										robot:setspeed(0) robot:setturn(0)
										return "armdown"
									end
								end
							end
							return "turnback"
						end end end
					end
					if frontcheck(sensor[i]) == true and sensor[i].type == WALL then	-- 2 wall
						--print("touchwall");
						--[[
						if carrying == true then
							print("armdown");
							father.data.unloadsig = sensor[i]
							robot:setspeed(0) robot:setturn(0)
							return "armdown"
						else
							return "turnback"
						end
						--]]
						return "turnback"
					end
				end
				robot:setturn((math.random()-0.5)*1800)
				robot:setspeed(0.5)
			end},

		------------------------------------------------------------------
		turnback = {method = 
			function(_currentstate,father)
				--print("turnback")
				father.data.turncount = 180
				robot:setspeed(0)
				return "turnbackstep"
			end},
		turnbackstep = {method = 
			function(_currentstate,father)
				--print("turnbackstep")
				local turnspeed = 90 * 10
				local turnL = turnspeed * steptime	-- steptime is global
				father.data.turncount = father.data.turncount - turnL
				robot:setturn(turnspeed)
				if father.data.turncount < turnL then
					return "random"
				end
			end},
		------------------------------------------------------------------

		------------------------------------------------------------------
		armup = {method = 
			function(_currentstate,father)
				father.data.armcount = 0
				robot:setspeed(0)
				robot:setturn(0)
				return "armupstep"
			end},
		armupstep = {method = 
			function(_currentstate,father)
				local armspeed = father.data.armspeed
				local armL = armspeed * steptime	-- steptime is global
				father.data.armcount = father.data.armcount + armL
				if father.data.armcount > 90 then
					robot:setarm(90)
					if father.data.turnbackflag == 1 then
						father.data.turnbackflag = 0
						return "turnback"
					else
						return "random"
					end
				end
				robot:setarm(father.data.armcount)
			end},
		armdown = {method = 
			function(_currentstate,father)
				father.data.armcount = 90
				robot:setspeed(0)
				robot:setturn(0)
				return "armdownstep"
			end},
		armdownstep = {method = 
			function(_currentstate,father)
				local armspeed = father.data.armspeed
				local armL = armspeed * steptime	-- steptime is global

				-- check box hit, goto armup
				print("sensor.n",sensor.n)
				for i = 1, sensor.n do
					--if sensor[i].type == BOX and sensor[i].beingcarried == false then	-- a uncarried box
					if sensor[i].type == BOX then	-- a uncarried box
						print("meet a box when armdown")
						local l = Vec3:create(sensor[i].l.x,sensor[i].l.y,sensor[i].l.z)
						print("l = ",l)
						print("unloadsig.l = ",father.data.unloadsig.l)
						print("len = ",(l - father.data.unloadsig.l):len())
						if (l - father.data.unloadsig.l):len() < boxsize then
							print("find a hit")
							father.data.turnbackflag = 1
							return "armupstep"
						end
				   end
				end

				father.data.armcount = father.data.armcount - armL
				if father.data.armcount < 0 then
					robot:setarm(0)
					local sig = father.data.unloadsig
					robot:tounload(	sig.l.x,sig.l.y,sig.l.z,
									sig.dF.x,sig.dF.y,sig.dF.z,
									sig.dU.x,sig.dU.y,sig.dU.z)
					return "random"
				end
				robot:setarm(father.data.armcount)
			end},
		------------------------------------------------------------------

	},
	initial = "random",
	transitions = {},
}

--------------------------------------------------------------------------
--------------------------------------------------------------------------
function init()
	--print("robot lua init",robot)
	robot:setspeed(1)
end

function step()
	movestate:stepSingle()
	--[[
	robot:setturn(30);
	print("n = ",sensor.n);
	for i = 1 , sensor.n do
		print("sensor",i,"l = ",sensor[i].l.x,
								sensor[i].l.y,
								sensor[i].l.z);
		print("sensor",i,"dF = ",sensor[i].dF.x,
								sensor[i].dF.y,
								sensor[i].dF.z);
		print("sensor",i,"dU = ",sensor[i].dU.x,
								sensor[i].dU.y,
								sensor[i].dU.z);
	end
	--]]
end

function destroy()
	--print("robot lua destroy")
end
