import pandas as pd

# create a sample dataframe
df = pd.DataFrame({
    'Year': [2019, 2019, 2020, 2020],
    'Quarter': ['Q1', 'Q2', 'Q1', 'Q2'],
    'Revenue': [100, 200, 150, 250]
})

print(df)

# set Year and Quarter columns as multiindex
df = df.set_index(['Year', 'Quarter'])

# show the result
print(df)

print('==========')


df = pd.DataFrame({
    'Year': [2019, 2019, 2020, None],
    'Quarter': ['Q1', 'Q2', 'Q3', 'Q4'],
    'Revenue': [100, 200, 150, 250]
})

print(df)

# set Year and Quarter columns as multiindex
df = df.set_index(['Year', 'Quarter'])

# show the result
print(df)