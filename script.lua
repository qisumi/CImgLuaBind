local img = ImgUInt8()

img:loadBmp("circuit.bmp")
img:setGray()

local height = img:height()
local width = img:width()

for x=0,width-1,1 do
    for y=0,height-1,1 do
        if(x<width/2) then
            img:setXY(x,y,0)
        else
            img:setXY(x,y,255)
        end
    end
end

img:display("test")