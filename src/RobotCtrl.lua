luaPath_src = ';../src/'
luaExt = '?.lua'
package.path = package.path .. luaPath_src .. "Lua/" .. luaExt
local State = require("State")

local movestate = State:create
{
	id = "RobotController",
	data = {turncount = 0,
	},
	substates = {
		random = {method = 
			function(_currentstate,father) 
				robot:setturn((math.random()-0.5)*1800)
				robot:setspeed(1)
				return "turnback"
			end},
		turnback = {method = 
			function(_currentstate,father)
				--print("turnback")
				father.data.turncount = 180
				return "turnbackstep"
			end},
		turnbackstep = {method = 
			function(_currentstate,father)
				--print("turnbackstep")
				local turnspeed = 90 * 10
				local turnL = turnspeed * steptime	-- steptime is global
				father.data.turncount = father.data.turncount - turnL
				robot:setspeed(0)
				robot:setturn(turnspeed)
				if father.data.turncount < turnL then
					return "random"
				end
			end},
	},
	initial = "random",
	transitions = {},
}

function init()
	--print("robot lua init",robot)
	robot:setspeed(1)
end

function step()
	movestate:stepSingle()
	print("robot lua step",steptime)
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
	print("robot lua destroy")
end
