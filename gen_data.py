import os;
for sep in range(-50, 50): # -0.50 to 0.49
  for mu in range(1, 201):
    os.system(f"./out/flow {sep/100} {mu/100}")

"""
sep = 30
for mu in range (1, 300):
  os.system(f"./out/flow {sep/100} {mu/100}")

for mu in range(1, 1001):
  #print(f"rho: {rho/10} mu: {mu/10}")
  os.system(f"./out/flow {sep/100} {mu/10}")
"""