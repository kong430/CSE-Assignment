import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np

def render():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glEnable(GL_DEPTH_TEST)
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE )
    glLoadIdentity()
    
    myOrtho(-5,5, -5,5, -8,8)
    myLookAt(np.array([5,3,5]), np.array([1,1,-1]), np.array([0,1,0]))

    # Above two lines must behaves exactly same as the below two lines

    #glOrtho(-5,5, -5,5, -8,8)
    #gluLookAt(5,3,5, 1,1,-1, 0,1,0)

    drawFrame()
    
    glColor3ub(255, 255, 255)
    drawCubeArray()
    
def myOrtho(left, right, bottom, top, near, far):
    # implement here
    orthM = np.array([[2./(right-left), 0, 0, -(right+left)/(right-left)],
                      [0, 2/(top-bottom), 0, -(top+bottom)/(top-bottom)],
                      [0, 0, -2/(far-near), -(far+near)/(far-near)],
                      [0, 0, 0, 1]])
    glMultMatrixf(np.transpose(orthM))

    
def myLookAt(eye, at, up):
    # implement here
    P1 = eye - at
    w = P1 / np.sqrt(np.dot(P1,P1))

    P2 = np.cross(up,w)
    u = P2 / np.sqrt(np.dot(P2,P2))

    v = np.cross(w,u)

    lookM = np.array([[u[0],u[1],u[2],-np.dot(u,eye)],
                      [v[0],v[1],v[2],-np.dot(v,eye)],
                      [w[0],w[1],w[2],-np.dot(w,eye)],
                      [0.,0.,0.,1.]])

    glMultMatrixf(np.transpose(lookM))

def drawUnitCube():
    glBegin(GL_QUADS)
    glVertex3f( 0.5, 0.5,-0.5)
    glVertex3f(-0.5, 0.5,-0.5)
    glVertex3f(-0.5, 0.5, 0.5)
    glVertex3f( 0.5, 0.5, 0.5)
    glVertex3f( 0.5,-0.5, 0.5)
    glVertex3f(-0.5,-0.5, 0.5)
    glVertex3f(-0.5,-0.5,-0.5)
    glVertex3f( 0.5,-0.5,-0.5)
    glVertex3f( 0.5, 0.5, 0.5)
    glVertex3f(-0.5, 0.5, 0.5)
    glVertex3f(-0.5,-0.5, 0.5)
    glVertex3f( 0.5,-0.5, 0.5)
    glVertex3f( 0.5,-0.5,-0.5)
    glVertex3f(-0.5,-0.5,-0.5)
    glVertex3f(-0.5, 0.5,-0.5)
    glVertex3f( 0.5, 0.5,-0.5)
    glVertex3f(-0.5, 0.5, 0.5)
    glVertex3f(-0.5, 0.5,-0.5)
    glVertex3f(-0.5,-0.5,-0.5)
    glVertex3f(-0.5,-0.5, 0.5)
    glVertex3f( 0.5, 0.5,-0.5)
    glVertex3f( 0.5, 0.5, 0.5)
    glVertex3f( 0.5,-0.5, 0.5)
    glVertex3f( 0.5,-0.5, -0.5)
    glEnd()

def drawCubeArray():
    for i in range (5):
        for j in range (5):
            for k in range (5):
                glPushMatrix()
                glTranslatef(i, j, -k-1)
                glScalef(.5,.5,.5)
                drawUnitCube()
                glPopMatrix()
               
def drawFrame():
    glBegin(GL_LINES)
    glColor3ub(255, 0, 0)
    glVertex3fv(np.array([0., 0., 0.]))
    glVertex3fv(np.array([1., 0., 0.]))
    glColor3ub(0, 255, 0)
    glVertex3fv(np.array([0., 0., 0.]))
    glVertex3fv(np.array([0., 1., 0.]))
    glColor3ub(0, 0, 255)
    glVertex3fv(np.array([0., 0., 0]))
    glVertex3fv(np.array([0., 0., 1.]))
    glEnd()

def main():
    if not glfw.init():
        return
    window = glfw.create_window(480,480,'2018008331', None,None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)
    
    # set the number of screen refresh to wait before calling glfw.swap_buffer().
    # if your monitor refresh rate is 60Hz, the while loop is repeated every 1/60 sec
    glfw.swap_interval(1)
    
    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ == "__main__":
    main()

