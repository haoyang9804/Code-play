import pandas as pd
import random
import numpy as np
codes = ["one","two","three"];
colours = ["black", "white"];
textures = ["soft", "hard"];
N= 100 # length of the dataframe
df = pd.DataFrame({ 'id' : range(1,N+1),
                    'weeks_elapsed' : [random.choice(range(1,25)) for i in range(1,N+1)],
                    'code' : [random.choice(codes) for i in range(1,N+1)],
                    'colour': [random.choice(colours) for i in range(1,N+1)],
                    'texture': [random.choice(textures) for i in range(1,N+1)],
                    'size': [random.randint(1,100) for i in range(1,N+1)],
                    'scaled_size': [random.randint(100,1000) for i in range(1,N+1)]
                   },  columns= ['id', 'weeks_elapsed', 'code','colour', 'texture', 'size', 'scaled_size'])
print(df)
grouped = df.groupby(['code', 'colour']).agg( {'size': [np.sum, np.average, np.size, pd.Series.idxmax],'scaled_size': [np.sum, np.average, np.size, pd.Series.idxmax]}).reset_index()
print(grouped)