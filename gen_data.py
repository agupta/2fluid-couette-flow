import numpy as np
from tqdm import tqdm
import os

for sep in tqdm(np.linspace(0.01, 0.99, num=50)):
    for mu_r in tqdm(np.geomspace(0.01, 1000, num=50), desc=f"sep={sep}"):
        os.system(f"./out/flow {sep} {mu_r} >/dev/null 2>&1")
        # >/dev/... suppresses output
