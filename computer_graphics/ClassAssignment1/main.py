import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

x_rotate = 0
y_rotate = 0

x_translate = 0
y_translate = 0

scene_x = 0
scene_y = 0

fovy = 30

flag_left_press = False
flag_right_press = False

def drawFrame():
    glBegin(GL_LINES)
    glColor3ub(255, 0, 0)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([1.,0.,0.]))
    glColor3ub(0, 255, 0)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([0.,1.,0.]))
    glColor3ub(0, 0, 255)
    glVertex3fv(np.array([0.,0.,0]))
    glVertex3fv(np.array([0.,0.,1.]))
    glEnd()

def drawXZ():
    glBegin(GL_LINES)
    glColor3ub(255, 255, 255)
    for i in range(-50,51):
        glVertex3fv(np.array([i,0,50]))
        glVertex3fv(np.array([i,0,-50]))
        glVertex3fv(np.array([50,0,i]))
        glVertex3fv(np.array([-50,0,i]))
    glEnd()

def drawSphere(numLats, numLongs, size, x_ratio, y_ratio, z_ratio):
    for i in range(0, numLats + 1):
        lat0 = np.pi * (-0.5 + float(float(i - 1) / float(numLats)))
        z0 = np.sin(lat0) * size
        zr0 = np.cos(lat0) * size

        lat1 = np.pi * (-0.5 + float(float(i) / float(numLats)))
        z1 = np.sin(lat1) * size
        zr1 = np.cos(lat1) * size

        # Use Quad strips to draw the sphere
        glBegin(GL_QUAD_STRIP)

        for j in range(0, numLongs + 1):
            lng = 2 * np.pi * float(float(j - 1) / float(numLongs))
            x = np.cos(lng)
            y = np.sin(lng)
            glVertex3f(x * zr0 * x_ratio, y * zr0 * y_ratio, z0 * z_ratio)
            glVertex3f(x * zr1 * x_ratio, y * zr1 * y_ratio, z1 * z_ratio)
        
        glEnd()

def drawPerson():
    t = glfw.get_time()
    glColor3ub(249, 149, 206)
    # draw body
    glPushMatrix()
    glTranslatef(0, 3, 0)
    glTranslatef(0,np.sin(8*t)*1.5,0)
    drawSphere(70,70,5,.2,.5,.2)
    
    # draw head
    glColor3ub(255, 238, 221)
    glPushMatrix()
    glTranslatef(0,3.2,0)
    drawSphere(70,70,1, 1, 1, 1)
    glPopMatrix()

    # draw arm right-1
    glColor3ub(249, 149, 206)
    glPushMatrix()
    glTranslatef(0, 2, .5)
    glRotatef(-70,1,0,0)
    glRotate(-np.sin(8*t)*70,1,0,0)
    glTranslate(0,-1.2,0)
    drawSphere(20,20,.6,.3,2,.3)

    #draw arm right-2
    glPushMatrix()
    glTranslatef(0,-1.1,.1)
    glRotate(-10,1,0,0)
    glRotate(-(np.sin(8*t)*70+20),1,0,0)
    glTranslate(0,-.7,0)
    drawSphere(20,20,.5,.3,2,.3)

    #draw arm right-3
    glColor3ub(255, 238, 221)
    glPushMatrix()
    glTranslatef(0,-.7,.2)
    glRotate(np.sin(8*t)*30,1,0,0)
    glTranslate(0,-.5,-.2)
    drawSphere(20,20,.5,.3,.7,.3)
    glPopMatrix()
    glPopMatrix()

    glPopMatrix()

    # draw arm left-1
    glColor3ub(249, 149, 206)
    glPushMatrix()
    glTranslatef(0, 2, -.5)
    glRotatef(70,1,0,0)
    glRotate(np.sin(8*t)*70,1,0,0)
    glTranslate(0,-1.2,0)
    drawSphere(20,20,.6,.3,2,.3)

    #draw arm left-2
    glColor3ub(249, 149, 206)
    glPushMatrix()
    glTranslatef(0,-1.1,-.1)
    glRotate(-10,1,0,0)
    glRotate(np.sin(8*t)*70+20,1,0,0)
    glTranslate(0,-.7,0)
    drawSphere(20,20,.5,.3,2,.3)

    #draw arm left-3
    glColor3ub(255, 238, 221)
    glPushMatrix()
    glTranslatef(0,-.7,-.2)
    glRotate(-np.sin(8*t)*30,1,0,0)
    glTranslate(0,-.5,.2)
    drawSphere(20,20,.5,.3,.7,.3)
    glPopMatrix()
    glPopMatrix()

    glPopMatrix()

    # draw leg right-1
    glColor3ub(68, 120, 196)
    glPushMatrix()
    glTranslatef(0, -2.5, 0)
    glRotatef(30, -1, 0, -1)
    glRotate(np.sin(8*t)*30,-1,0,-1)
    glTranslate(0,-1.5,.4)
    drawSphere(20,20,1,.25,1.7,.25)

    # draw leg right-2
    glPushMatrix()
    glTranslatef(-.1,-1.5,0)
    glRotatef(60,-1,0,-1)
    glRotate(np.sin(8*t)*60,-1,0,-1)
    glTranslate(0,-1,0)
    drawSphere(20,20,1,.15,1.2,.15)

    # draw leg right-3
    glColor3ub(214, 241, 127)
    glPushMatrix()
    glTranslatef(.4,-1.2,0)
    glRotatef(30,-1,0,-1)
    glRotate(np.sin(8*t)*30,-1,0,-1)
    glTranslate(0,0,0)
    drawSphere(20,20,1,.8,.2,.2)
    glPopMatrix()
    
    glPopMatrix()

    glPopMatrix()

    # draw leg left-1
    glColor3ub(68, 120, 196)
    glPushMatrix()
    glTranslatef(0, -2.5, -0)
    glRotatef(30, 1, 0, -1)
    glRotate(np.sin(8*t)*30,1,0,-1)
    glTranslate(0,-1.5,-.4)
    drawSphere(20,20,1,.25,1.7,.25)

    # draw leg left-2
    glPushMatrix()
    glTranslatef(-.1,-1.5,0)
    glRotatef(60, 1, 0, -1)
    glRotate(np.sin(8*t)*60,1,0,-1)
    glTranslate(0,-1,0)
    drawSphere(20,20,1,.15,1.2,.15)

    # draw leg left-3
    glColor3ub(214, 241, 127)
    glPushMatrix()
    glTranslatef(.4,-1.2,0)
    glRotatef(30,1,0,-1)
    glRotate(np.sin(8*t)*30,1,0,-1)
    glTranslate(0,0,0)
    drawSphere(20,20,1,.8,.2,.2)
    glPopMatrix()
    
    glPopMatrix()

    glPopMatrix()

    glPopMatrix()

def button_callback(window, button, action, mod):
    global flag_left_press, flag_right_press
    if button == glfw.MOUSE_BUTTON_LEFT:
        if action == glfw.PRESS:
            flag_left_press = True
        elif action == glfw.RELEASE:
            flag_left_press = False
    elif button == glfw.MOUSE_BUTTON_RIGHT:
        if action == glfw.PRESS:
            flag_right_press = True
        elif action == glfw.RELEASE:
            flag_right_press = False
            
def cursor_callback(window, xpos, ypos):
    global x_rotate, y_rotate
    global x_translate, y_translate
    global scene_x, scene_y
    if flag_left_press == True:
        x_rotate -= xpos - scene_x
        y_rotate -= ypos - scene_y
    elif flag_right_press == True:
        x_translate -= xpos - scene_x
        y_translate -= ypos - scene_y
    scene_x = xpos
    scene_y = ypos            

def scroll_callback(window, x, y):
    global fovy
    fovy -= y

def render():
    global x_rotate, y_rotate
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)     
    glEnable(GL_DEPTH_TEST)     
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE )
    
    glLoadIdentity() 
    gluLookAt(0, 0, -10., 0, 0, 0, 0., .1, 0)
	
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(fovy, 1, 10, 1000)
    glTranslatef(0., 0., -30)
    
    glMatrixMode(GL_MODELVIEW)
    glTranslatef(x_translate/30, 0., 0.)
    glTranslatef(0., y_translate/30, 0.)
  
    glRotatef(y_rotate/3, 1., 0., 0.)
    glRotatef(x_rotate/3, 0., 1., 0.)
    
    drawPerson()
    drawFrame()
    drawXZ()

def main():
    if not glfw.init():
        return
    window = glfw.create_window(520, 520, "201800331", None, None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)
    glfw.set_cursor_pos_callback(window, cursor_callback)
    glfw.set_mouse_button_callback(window, button_callback)
    glfw.set_scroll_callback(window, scroll_callback)

    glfw.swap_interval(1)

    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)
    glfw.terminate()
    
if __name__ == "__main__":
    main()
