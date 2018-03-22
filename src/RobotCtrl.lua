
function init()
	--print("robot lua init",robot)
	robot:setspeed(1);
end

function step()
	--print("robot lua step",robot)
	robot:setturn(30);
end

function destroy()
	print("robot lua destroy")
end
