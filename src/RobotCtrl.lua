
function init()
	print("lua init",robot)
	robot:setspeed(2);
end

function step()
	print("lua step",robot)
	robot:setspeed(3);
end

function destroy()
	print("lua destroy")
end
