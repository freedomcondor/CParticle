

--[[
  global:
  	box: xxx

--]]
function init()
	--print("box lua init",box)
end

function step()
	for i = 1, sensor.n do

	end
	--print("box lua step",box)
	--print("boxbeing carried",beingcarried)
	--[[
	print("box n = ",sensor.n);
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
	--box:setturn(-40);
end

function destroy()
	--print("box lua destroy")
end
