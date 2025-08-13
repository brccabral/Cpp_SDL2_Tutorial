# SDL2 Tutorial

Tutorial from Mike Shah https://www.youtube.com/watch?list=PLvv0ScY6vfd-p1gSnbQhY7vMe2rng0IL0

## glad setup

### Option 1

Clone `glad` and install requirements.txt

```shell
git clone --depth=1 https://github.com/Dav1dde/glad.git
cd glad
uv venv
. .venv/bin/activate
uv pip install -r requirements.txt
```

Edit file `./utility/examples.sh`, comment all `start/end` and uncomment only `gl_sdl2.c`.  
Run `./utility/examples.sh`. It will generate a folder `build`, compile and run the example. Close the window, copy the
`build` contents into this project's `extras/glad` folder.

### Option 2

Find your version running `glxinfo`.  
Go to https://glad.dav1d.de/  
Select

- Language `C/C++`
- Specification `OpenGL`
- API gl `4.6`
- Profile `Core`
- Select all extensions with button `Add All`
- Press `Generate`
- Download `glad.zip`
