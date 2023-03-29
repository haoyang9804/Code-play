import pandas as pd
import math

df = pd.DataFrame({'1': [1, 2], '2': [1, 2], '3': [4, 123], 'cnt': [4, 4]})
# print(type(df))
print(df)
# print('what is df[\'3\']?')
# print(df['3'])
# print('what is 4 in df[\'3\']?')
# print(4 in df['3'].values)
# print(df['3'].values)

print(df.loc[df['1'] == 1].index[0])