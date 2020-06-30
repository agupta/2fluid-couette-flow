import os;

for rho in range(1, 301):
  for mu in range(1, 301):
    #print(f"rho: {rho/10} mu: {mu/10}")
    os.system(f"./out/flow {rho/10} {mu/10} >/dev/null 2>&1")