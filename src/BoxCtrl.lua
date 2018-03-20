
function init()
	print("box lua init",box)
	box:setspeed(1);
end

function step()
	print("box lua step",box)
	box:setturn(-40);
end

function destroy()
	print("box lua destroy")
end
