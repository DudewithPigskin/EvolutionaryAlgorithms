#!/usr/bin/env python3
import fileinput

inputFolder = '/home/kpeelen/workspace/git/EA/EvolutionaryAlgorithms/test/'
outputFolder = '/home/kpeelen/workspace/git/EA/EvolutionaryAlgorithms/test/output/'
nameSegment = "statistics_MAMaLGaM_problem35_run"

populations = [8, 16, 32, 64, 128, 256, 512, 1024, 2048]
bounds = [1, 5, 10, 50, 100, 200, 300, 400, 500]
elites = [0, 0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1]
seeds =[4242, 4343, 4444, 4545, 4646, 4747, 4848, 4949, 5050, 5151]


for population in populations:
    for seed in seeds:
        inputFileName = f"population{population}_{seed}"+nameSegment+f"{seed}.dat"
        outputFileName = f"pop_{population}_{seed}.csv"
        fin= open(inputFolder+inputFileName, 'r') 
        fout= open(outputFolder+outputFileName, 'w')
        for line in fin:
            data = line
            data = data.replace('Time (s)','Time(s)')
            data = data.replace("GD Appr.set ", "GD_Appr.set ")
            data = data.replace("IGD Appr.set", "IGD_Appr.set")
            data = data.replace("Hypervol. Appr.set", "")
            data = data.replace("GD Archive", "GD_Archive")
            data = data.replace("IGDX Archive", "IGDX_Archive")
            data = data.replace("SR Archive", "SR_Archive")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace(" ", ",")
            fout.write(data)
        fin.close()
        fout.close()


for bound in bounds:
    for seed in seeds:
        inputFileName = f"bounds{bound}_{seed}"+nameSegment+f"{seed}.dat"
        outputFileName = f"bound_{bound}_{seed}.csv"
        fin= open(inputFolder+inputFileName, 'r') 
        fout= open(outputFolder+outputFileName, 'w')
        for line in fin:
            data = line
            data = data.replace('Time (s)','Time(s)')
            data = data.replace("GD Appr.set ", "GD_Appr.set ")
            data = data.replace("IGD Appr.set", "IGD_Appr.set")
            data = data.replace("Hypervol. Appr.set", "")
            data = data.replace("GD Archive", "GD_Archive")
            data = data.replace("IGDX Archive", "IGDX_Archive")
            data = data.replace("SR Archive", "SR_Archive")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace(" ", ",")
            fout.write(data)
        fin.close()
        fout.close()

for elite in elites:
    for seed in seeds:
        inputFileName = f"Elite{elite}_{seed}"+nameSegment+f"{seed}.dat"
        outputFileName = f"elite_{elite}_{seed}.csv"
        fin= open(inputFolder+inputFileName, 'r') 
        fout= open(outputFolder+outputFileName, 'w')
        for line in fin:
            data = line
            data = data.replace('Time (s)','Time(s)')
            data = data.replace("GD Appr.set ", "GD_Appr.set ")
            data = data.replace("IGD Appr.set", "IGD_Appr.set")
            data = data.replace("Hypervol. Appr.set", "")
            data = data.replace("GD Archive", "GD_Archive")
            data = data.replace("IGDX Archive", "IGDX_Archive")
            data = data.replace("SR Archive", "SR_Archive")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace("  ", " ")
            data = data.replace(" ", ",")
            fout.write(data)
        fin.close()
        fout.close()
    
   
