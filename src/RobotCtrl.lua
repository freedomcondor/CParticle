luaPath_src = ';../src/'
luaExt = '?.lua'
package.path = package.path .. luaPath_src .. "Lua/" .. luaExt
local State = require("State")

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
		fixed = true/false
		if fixed == true
		stig = {n,1,2,3,4,5,6}
	}
--]]

local ROBOT = 0
local BOX = 1
local WALL = 2

local frontcheck = function(sig)
	if sig.l.x > 0 then
		return true
	else
		return false
	end
end

local movestate = State:create
{
	id = "RobotController",
	data = {turncount = 0,
			armcount = 0,
			armspeed = 90 * 10,
			unloadsig = nil,
	},
	substates = {
		random = {method = 
			function(_currentstate,father) 
				for i = 1, sensor.n do
					if frontcheck(sensor[i]) == true and sensor[i].type == ROBOT then	-- 0 box
						--return "turnback"
					end
					if frontcheck(sensor[i]) == true and sensor[i].type == BOX then	-- 1 box
						if carrying == false and sensor[i].fixed == false then	-- if can carry
							--print("carry");
							robot:tocarry(sensor[i].obj)
							return "armup"
						else
							print("stig",sensor[i].stig.n)
							return "turnback"
						end
					end
					if frontcheck(sensor[i]) == true and sensor[i].type == WALL then	-- 2 wall
						--print("touchwall");
						if carrying == true then
							print("armdown");
							father.data.unloadsig = sensor[i]
							robot:setspeed(0) robot:setturn(0)
							return "armdown"
						else
							return "turnback"
						end
						--return "turnback"
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
					return "random"
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
