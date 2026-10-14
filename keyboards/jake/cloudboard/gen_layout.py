import json
layout=[]
# Left half: rows 0-3, cols 0-6
for r in range(4):
  for c in range(7):
    layout.append({"matrix":[r,c],"x":c,"y":r})
# Right half: rows 4-7, cols 0-6 (shift x so it doesn't overlap visually)
for r in range(4,8):
  for c in range(7):
    layout.append({"matrix":[r,c],"x":c+8,"y":r-4})
print(json.dumps(layout, indent=2))