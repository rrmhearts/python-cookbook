from pathlib import Path
import shutil
import os

dirs= "src"

for d in os.listdir(dirs): # d chapter
    for pd in os.listdir( os.path.join(dirs, d) ): # pd project directory
        pddir = os.path.join(dirs, d, pd)
        if os.path.isdir(pddir):
            pdfiles = [ name for name in os.listdir(pddir) ] # if os.path.isfile(os.path.join(pddir, name))]
            numFiles = len(pdfiles)
            if numFiles == 1:
                ext = os.path.splitext(pdfiles[0])[-1]
                print (os.path.join(pddir, pdfiles[0]), pddir, ext)
                shutil.move(os.path.join(pddir, pdfiles[0]),\
                    f"{pddir}{ext}")
            # if numFiles == 0: # on a second run, or remove to delete on first run
                shutil.rmtree(pddir )

        # if not os.path.exists(os.path.join('src', pd)):
        #     shutil.move(os.path.join(dirs, d, pd), 'src')
    # if os.path.isdir(os.path.join(dirs, d)):
    #     shutil.rmtree(os.path.join(dirs, d) )