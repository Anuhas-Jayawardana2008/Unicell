function game:start()
	x = -0.954
end

speed = 0.09

function game:update()
	if(Input.getKeyDown(KEY_W))
	then
		y = y + speed
	end
	if(Input.getKeyDown(KEY_S))
	then
		y = y - speed
	end
end