local State = require("State")
local Controller = require("Controller")
local BoxController = {CLASSBoxController = true}
BoxController.__index = BoxController
setmetatable(BoxController, Controller)

function BoxController:create(x)
	-- x is supposed to be a robot
	instance = Controller:create()
	setmetatable(instance, self)

	if x.CLASSBox ~= true then
		return instance
	end

	instance.box = x
	instance:init()
	return instance
end

function BoxController:init()
	-- define state
	self.state = State:create
	{
		id = "BoxController",
		data = {box = self.box,
				update_cue = nil},
		substates = 
		{
			donothing = {method = 
				function(_currentstate,father)
					--local box = father.data.box
					if father.data.update_cue == true then
						father.data.update_cue = nil
						return "updatestig"
					end
				end},
			updatestig = {method =
				function(_currentstate,father)
					local box = father.data.box
					local sig = box.sensor.signal
					-- scan signal, if a box, delete my stig pointing it
					--				if a stig, add a stig with the dir
					--	scan stig first
					box:addStig("front")
					box:addStig("back")
					box:addStig("left")
					box:addStig("right")

					for i = 1, sig.n do
						if sig[i].obj.CLASSStig == true then
							-- add new stig
							---[[
							--]]
							-- update this stig's box
							sig[i].obj.box.myCtrl.state.data.update_cue = true
						end
					end
					for i = 1, sig.n do
						if sig[i].obj.CLASSBox == true then
							j = 1
							while j <= box.stig.n do
								-- check
								if (sig[i]:nor() - box.stig[j].rel):len()<0.5 then
									box:delStig(j)
									j = j - 1
								end
								j = j + 1
							end
							-- delete old stig
						end
					end
					return "donothing"
				end},
		},

		initial = "donothing",
		transitions = 
		{
			--[[
			{	from = "forward", to = "backup",
				condition = function(dt)
								local sig = dt.robot.sensor.signal
								if sig.n == 1 and sig[1].x > 0 then
									return true
								else
									return false
								end
							end
			},
			{	from = "backup", to = "forward",
				condition = function(dt)
								local sig = dt.robot.sensor.signal
								if sig.n == 1 and sig[1].x < 0 then
									return true
								else
									return false
								end
							end
			},
			--]]
		}
	}
	--]]
end

function BoxController:step(time)
	self.state:stepSingle()
end

function BoxController:exit()
	Controller:exit(self)
	self.box = nil
end

return BoxController
