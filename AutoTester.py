import subprocess

populations = [8, 16, 32, 64, 128, 256, 512, 1024, 2048]
bounds = [1, 5, 10, 50, 100, 200, 300, 400, 500]
elites = [0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1]
seeds =[4242, 4343, 4444, 4545, 4646, 4747, 4848, 4949, 5050, 5151]
commandStart = ['/home/kpeelen/workspace/git/EA/EvolutionaryAlgorithms/mamalgam']
commandSettings = ['-s' ,'35' , '30']
basicBounds = ['-50', '50']
basicPop = ['256', '128', '64']
commandEnd = ['500000', '6000', '0']

# for pop in populations:
#     for seed in seeds:
#         commandPop = [f"{pop}", f"{int(pop/2)}", f"{int(pop/4)}"]
#         naming = [f"./test/population{pop}_{seed}"]
#         seedName = [f"{seed}"]
#         command = commandSettings+ basicBounds + commandPop + commandEnd + seedName + naming
#         subprocess.run(commandStart+ command)


# for bound in bounds:
#     for seed in seeds:
#         commandBounds = [f"{-1*bound}", f"{bound}"]
#         naming = [f"./test/bounds{bound}_{seed}"]
#         seedName = [f"{seed}"]
#         command = commandSettings+ commandBounds+ basicPop+ commandEnd+ seedName+ naming
#         subprocess.run(commandStart+ command)

        
for elite in elites:
    standInPop =["256"]
    standInElite = int(256 * elite)
    standInEliteSet = int(256 / 2)
    for seed in seeds:
        commandElite = [f"{standInElite}" ,f"{standInEliteSet}"]
        naming = [f"./test/Elite{elite}_{seed}"]
        seedName = [f"{seed}"]
        command = commandSettings+basicBounds+ standInPop+ commandElite+ commandEnd+ seedName+ naming
        subprocess.run(commandStart+ command)
