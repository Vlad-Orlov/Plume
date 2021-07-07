from ROOT import TH1D, TCanvas
from alarm import *

inFile = open("log.txt")
lines = inFile.readlines()


histIn = TH1D("mean inside", "meanInside", 60, 0, 10)
histOut = TH1D("mean outside", "meanOutside", 300, 0, 6)

for i in lines[0::2]:
	histIn.Fill(float(i))

for i in lines[1::2]:
	histOut.Fill(float(i))


c = TCanvas("mean","mean", 1000,500)
c.Divide(2,1)

c.cd(1)
histIn.Draw()
c.cd(2)
histOut.Draw()

alarm = Alarm()
alarm.send_message("Finished!")

try:
	input()
except:
	pass