import numpy as np
import math
import glfw
from OpenGL.GL import *

pri_type_set = GL_LINE_LOOP

def key_callback(window, key, scancode, action, mods):
    global pri_type_set
    pri_type_set = GL_LINE_LOOP
    if key==glfw.KEY_1:
        pri_type_set = GL_POINTS
    elif key==glfw.KEY_2:
        pri_type_set = GL_LINES
    elif key==glfw.KEY_3:
        pri_type_set = GL_LINE_STRIP
    elif key==glfw.KEY_4:
        pri_type_set = GL_LINE_LOOP
    elif key==glfw.KEY_5:
        pri_type_set = GL_TRIANGLES
    elif key==glfw.KEY_6:
        pri_type_set = GL_TRIANGLE_STRIP
    elif key==glfw.KEY_7:
        pri_type_set = GL_TRIANGLE_FAN
    elif key==glfw.KEY_8:
        pri_type_set = GL_QUADS
    elif key==glfw.KEY_9:
        pri_type_set = GL_QUAD_STRIP
    elif key==glfw.KEY_0:
        pri_type_set = GL_POLYGON

def render():
    pri_type = GL_LINE_LOOP
    pri_type = pri_type_set
    num = np.linspace(0, 330, 12)
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()
    glBegin(pri_type)
    for i in num:
        i = math.radians(i)
        glVertex2f(np.cos(i), np.sin(i))
    glEnd()
    
def main():
    if not glfw.init():
        return
    window = glfw.create_window(480, 480, "2018008331", None, None)
    if not window:
        glfw.terminate()
        return

    glfw.set_key_callback(window, key_callback)
 
    glfw.make_context_current(window)

    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ =="__main__":
    main()
