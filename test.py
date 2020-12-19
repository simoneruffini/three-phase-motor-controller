import math

bus_freq = 170 * 10**6
prescaler = 4 ## grater than one or slow the bus speed
cntr_hz=bus_freq/prescaler

samp_freq=4*10**3
inp_freq=50

period_samp=(int)(samp_freq/inp_freq)

max_value = 0

while True:
    max_value=cntr_hz/(samp_freq)
    print(max_value,(int)(max_value),max_value%(int)(max_value))
    if (max_value%(int)(max_value))<0.01 :
        break
    period_samp -= 1

print("sampling per period: "+ str(period_samp) +", counter max value:"+ str(max_value))

half_period_samp=(int)(period_samp / 2)

a=[]
c=0
for val in range(0,period_samp):
    a.append((int)((max_value*(1+math.sin(c)))/2))
    print("x: "+str(c)+" sin: "+str(a[-1]))
    c+=2*math.pi/period_samp

print("bus frequency: "+ str(bus_freq) +", prescaler: "+ str(prescaler))
print("sampling per period: "+ str(period_samp) +", counter max value:"+ str(max_value))
print(a)
