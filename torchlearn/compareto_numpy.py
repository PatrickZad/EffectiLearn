import torch
import numpy as np
npData=np.arange(6).reshape((2,3))
torchData=torch.from_numpy(npData)
npData=torchData.numpy()
print('done !')