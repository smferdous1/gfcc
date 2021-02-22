
import os
import sys
import glob
import pandas as pd


def read_col(fname, col=1, convert=int, sep=None):
    """Read text files with columns separated by `sep`.

    fname - file name
    col - index of column to read
    convert - function to convert column entry with
    sep - column separator
    If sep is not specified or is None, any
    whitespace string is a separator and empty strings are
    removed from the result.
    """
    with open(fname) as fobj:
         return [convert(line.split(sep)[col]) for line in fobj]

def main(inputDir, combinedFile):
    os.chdir(inputDir)
    fileList = ['s1t_stats','s1v_stats','d1t_stats','d1v_stats','d2t_stats','d2v_stats']
    #print fileList
    df = pd.DataFrame()
    df.fillna(0)
    #with open(combinedFile,'r') as cf:
    for cacheLog in fileList:
        col_name = cacheLog.split("_")[0]
        hits_col = read_col(cacheLog,1,int,":")
        df[col_name] = hits_col
    
    df.to_csv(combinedFile+".csv",index_label='index')
    print df
        

if __name__=="__main__":
    inputDir = sys.argv[1]
    combinedFileName = sys.argv[2]
    main(inputDir, combinedFileName)
