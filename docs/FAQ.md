## FAQ

## If you plan to use a basisset file not provided by this library (via LibInt)

- Download a basis file in `Gaussian` format from https://www.basissetexchange.org/
- Copy the file to the folder: `$GFCC_INSTALL_PATH/share/libint/2.7.0/basis/`
- Check the line before the start of Hydrogen(H) atom in the basis file to see if it contains the marker `****` If not, please add this marker.

e.g:

```
****
H     0
```

## How to fix the "undefined reference to `hbw_free'" error?

This error might occur during the final stage of the gfcc compilation. Please add the extra option -DTAMM_EXTRA_LIBS="-lmemkind" to cmake.
```
cmake -DCMAKE_INSTALL_PREFIX=$GFCC_INSTALL_PATH -DTAMM_EXTRA_LIBS="-lmemkind" ..
```

## Job crashes with Bus error

This is a known issue that occurs when limited amount of memory is available.  
https://github.com/spec-org/gfcc/issues/1
