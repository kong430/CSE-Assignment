import math
import glfw
from OpenGL.GL import *
import numpy as np

key_input = list()

def key_callback(window, key, scancode, action, mods):

    global key_input

    if action==glfw.PRESS or action==glfw.REPEAT:
        if key==glfw.KEY_Q:
               key_input.append('Q')

        elif key==glfw.KEY_E:
                key_input.append('E')
            
        elif key==glfw.KEY_A:
                key_input.append('A')

        elif key==glfw.KEY_D:
                key_input.append('D')
               
        elif key==glfw.KEY_1:
                key_input.append('1')
             
def render():
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()

    #draw coordinates
    glBegin(GL_LINES)
    glColor3ub(255, 0, 0)
    glVertex2fv(np.array([0.,0.]))
    glVertex2fv(np.array([1.,0.]))
    glColor3ub(0, 255, 0)
    glVertex2fv(np.array([0.,0.]))
    glVertex2fv(np.array([0.,1.]))
    glEnd()

    glColor3ub(255, 255, 255)
    
    for i in reversed(key_input):
        if i =='Q':
            glTranslatef(-.1, 0., 0.)
        elif i=='E':
            glTranslatef(.1, 0., 0.)
        elif i=='A':
            glRotatef(10, 0, 0, 1)
        elif i=='D':
            glRotatef(-10, 0, 0, 1)
        elif i=='1':
            key_input.clear()
            glLoadIdentity()

    drawTriangle()
    
def drawTriangle():
    glBegin(GL_TRIANGLES)
    glVertex2fv(np.array([0.,.5]))
    glVertex2fv(np.array([0.,0.]))
    glVertex2fv(np.array([.5,0.]))
    glEnd()
    
def main():
    if not glfw.init():
        return
    window = glfw.create_window(480,480,"2018008331", None,None)
    if not window:
        glfw.terminate()
        return

    glfw.set_key_callback(window, key_callback)
    glfw.make_context_current(window)
    glfw.swap_interval(1)

    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
   
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ == "__main__":
    main()
