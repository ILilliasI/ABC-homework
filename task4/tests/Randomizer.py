from random import randint

def GetRandomName():
    # length = randint(1, 20)
    length = 20
    name = ""
    
    for i in range(length):
        name += chr(randint(97, 122))
    return name;

plantsCount = 10000
file = open("test09.txt", "w")

for i in range(plantsCount):
    plantType = randint(1, 3)
    file.write(str(plantType) + "\n")

    name = GetRandomName()
    file.write(name)
    
    if (plantType == 1):
        age = randint(0, 2147483647)
        file.write(" " + str(age))
    elif (plantType == 2):
        floweringMonth = randint(1, 12)
        file.write(" " + str(floweringMonth))
    else:
        bushType = randint(1, 3)
        file.write(" " + str(bushType))
    if (i != plantsCount - 1):
        file.write("\n")
file.close()
