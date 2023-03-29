import pandas as pd

df = pd.DataFrame({'1': [1], '2': [1], '3': [4], 'cnt': [4]})
print(df)
print('what is df[\'3\']?')
print(df['3'])
print('what is 4 in df[\'3\']?')
print(4 in df['3'].values)