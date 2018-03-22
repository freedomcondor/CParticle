
function init()
	--print("robot lua init",robot)
	robot:setspeed(1);
end

function step()
	--print("robot lua step",robot)
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
end

function destroy()
	print("robot lua destroy")
end
