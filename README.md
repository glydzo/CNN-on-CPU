# CNN inference on CPU using frugally-deep
The aim of this project is to perform inference of a CNN on CPU using the [frugally-deep](https://github.com/Dobiasd/frugally-deep) library. Thus, it is possible to train a model using Keras or Tensorflow in python, save it in h5 format and then convert it into a format usable by frugally-deep in order to perform the prediction directly from a c++ program.

## Setting up the environment

### Verify your cmake version
To install [frugally-deep](https://github.com/Dobiasd/frugally-deep), you need cmake 3.14 or higher. You can check your cmake version by executing:
`cmake --version`

>If your version of cmake is too old, you should upgrade it (see https://cmake.org/download/).

### Install cnpy
The library [cnpy](https://github.com/rogersce/cnpy) allows you to open and load .npy files (numpy) in a c++ program.
To install it properly, you can run the following commands in a shell:

```bash
sudo apt-get install zlib1g zlib1g-dev
git clone https://github.com/rogersce/cnpy
cd cnpy/
mkdir build
cd build/
cmake ..
make
sudo make install
```

### Install tqdm
In order to facilitate the visualisation of the prediction progress, we use a c++ version of tqdm. This is a header-only. You just have to copy the header to the right place by running the following command:

```bash
cd lib
sudo mkdir /usr/local/include/tqdm
sudo cp tqdm.h /usr/local/include/tqdm
```

### Install frugally-deep
Now you just have to run the installation script. It will take care of cloning the right directories and copying the files to be included in the right places.

```bash
cd tools
chmod +x setup.sh
sudo ./setup.sh
```

### Check your LD_LIBRARY_PATH
Be sure that /usr/local/lib is in the LD_LIBRARY_PATH environment variable.
You can achieve this automatically by adding this line at the end of your **~.profile** file:

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
```

## Testing the environment
Go to the root of the directory, create a **build** folder and simply do `make`.





