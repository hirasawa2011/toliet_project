f = open("TEST.txt")
db = f.read().splitlines()
db = list(map(int, db))
result = 0
for i in db:
    result = result + ((i*5)/3600)

result = str(result)
with open(r"Result.txt" , "w" , encoding="utf8") as r:
    r.write("Watt Result : " + result + " Wh")

