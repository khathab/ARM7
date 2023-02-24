time = 8531
minutes = int(time/6000);
seconds = int((time%6000)/100);
hundreds = int((time%6000)%100);

print(minutes,seconds,hundreds,sep=":")