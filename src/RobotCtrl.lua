
function init()
	print("lua init")
	robot:setspeed(2);
end

function step()
	print("lua step")
	robot:setspeed(3);
end

function destroy()
	print("lua destroy")
end
