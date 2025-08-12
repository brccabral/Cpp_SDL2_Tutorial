# SDL2 Tutorial

Tutorial from Mike Shah https://www.youtube.com/watch?list=PLvv0ScY6vfd-p1gSnbQhY7vMe2rng0IL0

## glad setup

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
