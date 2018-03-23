local State = require("State")
local Controller = require("Controller")
local RobotController = {CLASSRobotController = true}
RobotController.__index = RobotController
setmetatable(RobotController, Controller)

function RobotController:create(x)
	-- x is the robot it self
	instance = Controller:create()
	setmetatable(instance, self)

	if x.CLASSRobot ~= true then
		return instance
	end

	instance.robot = x
	instance.armstate = {}
	instance:init()
	return instance
end

function RobotController:init()
	-- define state
	self.state = State:create
	{
		id = "RobotMoveController",
		data = {robot = self.robot,
				apprSig = nil,
				steptime = 0.2,  -- overwrite by run()
				turncount = 0
			   },
		substates = 
		{
			forward = {method = 
				function(_currentstate,father) 
					--print("forward")
					father.data.robot:turn((math.random()-0.5)*30)
					father.data.robot:forwardStep(1.57)  
					--father.data.robot:forward(3.14)
				end},
			turnback = {method = 
				function(_currentstate,father)
					--print("turnback")
					father.data.turncount = 3.14
					return "turnbackstep"
				end},
			turnbackstep = {method = 
				function(_currentstate,father)
					--print("turnbackstep")
					local turnspeed = 1.57 * 10
					local turnL = turnspeed * father.data.steptime
					father.data.robot:forwardStep(0)  
					father.data.turncount = father.data.turncount - turnL
					father.data.robot:turn(turnspeed)
					if father.data.turncount < turnL then
						return "forward"
					end
				end},
			backup = {method = function(_currentstate,father) 
							father.data.robot:forwardStep(-1.57) end},
							--father.data.robot:forward(-3.14) end},
			approach = {method= 
				function(_currentstate,father) 
					--print("approach")
					local robot = father.data.robot
					local apprSig = father.data.apprSig
					if apprSig == nil or apprSig.lost == true then 
						apprSig = nil 
						return "forward" 
					end
					if apprSig.y > 0 then
						robot:turn(apprSig.y/apprSig.x*10)
					else if apprSig.y < 0 then
						robot:turn(apprSig.y/apprSig.x*10)
					else
						robot:turn(0)
					end end
					if apprSig.x < 0.10 and 
					   apprSig.y/apprSig.x < 1 and apprSig.y/apprSig.x >-1 and
					   robot.carrying == nil then
						--robot.carrying = apprSig.obj
						robot:toCarry(apprSig.obj)

						father.data.robot:forwardStep(0)  
						father.data.robot:turn(0)
							-- wait to lift arm
						return "armup"
					else if apprSig.x < 0.10 and
					   apprSig.y/apprSig.x < 1 and apprSig.y/apprSig.x >-1 and
					   robot.carrying ~= nil then
						robot.myCtrl.armstate.data.reachstig = true
						return "armdown"
					else
						robot:forwardStep(1.57)
					end end
				end},
			armup = {method = 
				function(_currentstate,father)
					if father.data.robot.myCtrl.armstate.current == "up" then
						return "forward"
					end
				end},
			armdown = {method = 
				function(_currentstate,father)
					if father.data.robot.myCtrl.armstate.current == "down" then
						father.data.robot:toRelease(father.data.apprSig.obj)
						return "turnback"
					end
				end},
		},

		initial = "forward",
		transitions = 
		{
			{from = "forward", to = "approach",
			 condition = 
			 	function(dt)
					local sig = dt.robot.sensor.signal
					if sig.n ~= 0 then
						for i = 1, sig.n do
							if sig[i].x > 0 and
							   sig[i].CLASSBox == true and 
							   sig[i].obj.fix == nil and
							   dt.robot.carrying == nil then
								dt.apprSig = sig[i]
								return true
							else if sig[i].x > 0 and
							   sig[i].CLASSStig == true and
							   dt.robot.carrying ~= nil then
								dt.apprSig = sig[i]
								return true
							end end
						end
					end
					return false
				end
			},
			{from = "forward", to = "turnback",
			 condition = 
			 	function(dt)
					local sig = dt.robot.sensor.signal
					if sig.n ~= 0 then
						for i = 1, sig.n do
							if sig[i].CLASSWall == true or
							  (((sig[i].CLASSBox == true and 
							   sig[i].obj.fix == true) or
							  (sig[i].CLASSRobot == true or
								dt.robot.carrying ~= nil)) and 
							 sig[i].y/sig[i].x<1 and sig[i].y/sig[i].x>-1 and
							 sig[i].x < 0.1 and sig[i].x > 0)then
								  --1. wall   2. another robot  3. i am carrying
								--dt.turncount = 3.14
								return true
							end
						end
					end
					return false
				end
			},
			{from = "approach", to = "turnback",
			 condition = 
			 	function(dt)
					local sig = dt.robot.sensor.signal
					if sig.n ~= 0 then
						for i = 1, sig.n do
							if sig[i].CLASSWall == true or
							  (((sig[i].CLASSBox == true and 
							   sig[i].obj.fix == true) or
							  sig[i].CLASSRobot == true) and
							 sig[i].y/sig[i].x<1 and sig[i].y/sig[i].x>-1 and 
							 sig[i].x < 0.1 and sig[i].x > 0)then
								return true
							end
						end
					end
					return false
				end
			},
		}
	}
	--- arm state -------------------------------------------------------
	self.armstate = State:create
	{
		id = "RobotArmController",
		data = {robot = self.robot, step = 15,
				steptime = 0.2,  -- overwrite by run()
				reachstig = nil,
			   },
			-- step is lifting speed, in degree
		substates = 
		{
			--down = {method = function(_currentstate,father) 
			--				father.data.robot:setArm(0) end},
			down = "down",
							--father.data.robot:forward(3.14) end},
			--up = {method = function(_currentstate,father) 
			--				father.data.robot:setArm(90) end},
			up = "up",
			movingup = {method = 
				function(_currentstate,father) 
					local arm = father.data.robot.arm
					arm = arm + father.data.step
					if arm > 90 then
						father.data.robot:setArm(90) 
						return "up"
					end
					father.data.robot:setArm(arm) 
				end},
			movingdown = {method = 
				function(_currentstate,father) 
					local arm = father.data.robot.arm
					arm = arm - father.data.step
					if arm < 0 then
						father.data.robot:setArm(0) 
						return "down"
					end
					father.data.robot:setArm(arm) 
				end},
		},

		initial = "down",
		transitions = 
		{
			{from = "down", to = "movingup",
			 condition = 
			 	function(dt)
					if dt.robot.carrying ~= nil then
						return true
					else
						return false
					end
				end
			},
			{from = "up", to = "movingdown",
			 condition = 
				function(dt)
					if dt.reachstig == true then
						dt.reachstig = nil
						return true
					end
				end
			},
		}
	}
end

function RobotController:step(time)
	-- time in s
	self.state.data.steptime = time
	self.armstate.data.steptime = time

	self.state:stepSingle()
	self.armstate:stepSingle()
end

function RobotController:exit()
	Controller:exit(self)
	self.robot = nil
end

return RobotController
