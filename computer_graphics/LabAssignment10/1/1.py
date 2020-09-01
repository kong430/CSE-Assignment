import glfw
from OpenGL.GL import *
from OpenGL.GLU import *
import numpy as np
from OpenGL.arrays import vbo
import ctypes

gCamAng = 0.
gCamHeight = 1.

def createVertexArraySeparate():
    varr = np.array([
            [0,1,0],            # v0 normal
            [ 0.5, 0.5,-0.5],   # v0 position
            [0,1,0],            # v1 normal
            [-0.5, 0.5,-0.5],   # v1 position
            [0,1,0],            # v2 normal
            [-0.5, 0.5, 0.5],   # v2 position

            [0,1,0],            # v3 normal
            [ 0.5, 0.5,-0.5],   # v3 position
            [0,1,0],            # v4 normal
            [-0.5, 0.5, 0.5],   # v4 position
            [0,1,0],            # v5 normal
            [ 0.5, 0.5, 0.5],   # v5 position

            [0,-1,0],           # v6 normal
            [ 0.5,-0.5, 0.5],   # v6 position
            [0,-1,0],           # v7 normal
            [-0.5,-0.5, 0.5],   # v7 position
            [0,-1,0],           # v8 normal
            [-0.5,-0.5,-0.5],   # v8 position

            [0,-1,0],
            [ 0.5,-0.5, 0.5],
            [0,-1,0],
            [-0.5,-0.5,-0.5],
            [0,-1,0],
            [ 0.5,-0.5,-0.5],

            [0,0,1],
            [ 0.5, 0.5, 0.5],
            [0,0,1],
            [-0.5, 0.5, 0.5],
            [0,0,1],
            [-0.5,-0.5, 0.5],

            [0,0,1],
            [ 0.5, 0.5, 0.5],
            [0,0,1],
            [-0.5,-0.5, 0.5],
            [0,0,1],
            [ 0.5,-0.5, 0.5],

            [0,0,-1],
            [ 0.5,-0.5,-0.5],
            [0,0,-1],
            [-0.5,-0.5,-0.5],
            [0,0,-1],
            [-0.5, 0.5,-0.5],

            [0,0,-1],
            [ 0.5,-0.5,-0.5],
            [0,0,-1],
            [-0.5, 0.5,-0.5],
            [0,0,-1],
            [ 0.5, 0.5,-0.5],

            [-1,0,0],
            [-0.5, 0.5, 0.5],
            [-1,0,0],
            [-0.5, 0.5,-0.5],
            [-1,0,0],
            [-0.5,-0.5,-0.5],

            [-1,0,0],
            [-0.5, 0.5, 0.5],
            [-1,0,0],
            [-0.5,-0.5,-0.5],
            [-1,0,0],
            [-0.5,-0.5, 0.5],

            [1,0,0],
            [ 0.5, 0.5,-0.5],
            [1,0,0],
            [ 0.5, 0.5, 0.5],
            [1,0,0],
            [ 0.5,-0.5, 0.5],

            [1,0,0],
            [ 0.5, 0.5,-0.5],
            [1,0,0],
            [ 0.5,-0.5, 0.5],
            [1,0,0],
            [ 0.5,-0.5,-0.5],
            # ...
            ], 'float32')
    return varr

def drawUnitCube_glDrawArray():
    global gVertexArraySeparate
    varr = gVertexArraySeparate
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_NORMAL_ARRAY)
    glNormalPointer(GL_FLOAT, 6*varr.itemsize, varr)
    glVertexPointer(3, GL_FLOAT, 6*varr.itemsize, ctypes.c_void_p(varr.ctypes.data + 3*varr.itemsize))
    glDrawArrays(GL_TRIANGLES, 0, int(varr.size/6))

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

#################################################
def l2norm(v):
    return np.sqrt(np.dot(v, v))

def normalized(v):
    l = l2norm(v)
    return 1/l * np.array(v)

def lerp(v1, v2, t):
    return (1-t)*v1 + t*v2

def exp(rv):
    theta = l2norm(rv)
    uv = normalized(rv)
    cos = np.cos(theta)
    sin = np.sin(theta)
    R = np.array([[cos + uv[0]*uv[0]*(1-cos), uv[0]*uv[1]*(1-cos)-uv[2]*sin, uv[0]*uv[2]*(1-cos)+uv[1]*sin],
                [uv[1]*uv[0]*(1-cos)+uv[2]*sin, cos+uv[1]*uv[1]*(1-cos), uv[1]*uv[2]*(1-cos)-uv[0]*sin],
                [uv[2]*uv[0]*(1-cos)-uv[1]*sin, uv[2]*uv[1]*(1-cos)+uv[0]*sin, cos+uv[2]*uv[2]*(1-cos)]])
    return R

def log(R):
    theta = np.arccos((R[0][0]+R[1][1]+R[2][2]-1)/2)
    v1 = (R[2][1]-R[1][2])/(2*np.sin(theta))
    v2 = (R[0][2]-R[2][0])/(2*np.sin(theta))
    v3 = (R[1][0]-R[0][1])/(2*np.sin(theta))
    rv = np.array([v1,v2,v3]) * theta
    return rv

def slerp(R1, R2, t):
    return R1 @ exp(t*log(R1.T@R2))

def interpolateRotVec(rv1, rv2, t):
    return exp(lerp(rv1, rv2, t))

def interpolateZYXEuler(euler1, euler2, t):
    return ZYXEulerToRotMat(lerp(euler1, euler2, t))

def interpolateRotMat(R1, R2, t):
    return lerp(R1, R2, t)


# euler[0]: zang
# euler[1]: yang
# euler[2]: xang
def ZYXEulerToRotMat(euler):
    zang, yang, xang = euler
    Rx = np.array([[1,0,0],
                   [0, np.cos(xang), -np.sin(xang)],
                   [0, np.sin(xang), np.cos(xang)]])
    Ry = np.array([[np.cos(yang), 0, np.sin(yang)],
                   [0,1,0],
                   [-np.sin(yang), 0, np.cos(yang)]])
    Rz = np.array([[np.cos(zang), -np.sin(zang), 0],
                   [np.sin(zang), np.cos(zang), 0],
                   [0,0,1]])
    return Rz @ Ry @ Rx

def drawCubes(brightness):
    glPushMatrix()
    glScalef(.5,.5,.5)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (.5*brightness,.5*brightness,.5*brightness,1.))
    drawUnitCube_glDrawArray()

    glTranslatef(1.5,0,0)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (1.*brightness,0.,0.,1.))
    drawUnitCube_glDrawArray()

    glTranslatef(-1.5,1.5,0)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (0.,1.*brightness,0.,1.))
    drawUnitCube_glDrawArray()

    glTranslatef(0,-1.5,1.5)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (0.,0.,1.*brightness,1.))
    drawUnitCube_glDrawArray()
    glPopMatrix()

#################################################
gVisibles = [True,False,False,False] # visible flags for slerp, interpolateZYXEuler, interpolateRotVec, interpolateRotMat
def render(ang):
    global gCamAng, gCamHeight
    global gVisibles
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)

    glEnable(GL_DEPTH_TEST)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45, 1, 1,10)

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(5*np.sin(gCamAng),gCamHeight,5*np.cos(gCamAng), 0,0,0, 0,1,0)

    drawFrame() # draw global frame

    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_RESCALE_NORMAL) # rescale normal vectors after transformation and before lighting to have unit length

    glLightfv(GL_LIGHT0, GL_POSITION, (1.,2.,3.,1.))
    glLightfv(GL_LIGHT0, GL_AMBIENT, (.1,.1,.1,1.))
    glLightfv(GL_LIGHT0, GL_DIFFUSE, (1.,1.,1.,1.))
    glLightfv(GL_LIGHT0, GL_SPECULAR, (1.,1.,1.,1.))

    # start orientation
    # ZYX Euler angles: rot z by -90 deg then rot y by 90 then rot x by 0
    euler1 = np.array([-1.,1.,0.])*np.radians(90)   # in ZYX Euler angles
    R1 = ZYXEulerToRotMat(euler1)  # in rotation matrix
    rv1 = log(R1)   # in rotation vector

    # end orientation
    # ZYX Euler angles: rot z by 0 then rot y by 0 then rot x by 90
    euler2 = np.array([0.,0.,1.])*np.radians(90)   # in ZYX Euler angles
    R2 = ZYXEulerToRotMat(euler2)  # in rotation matrix
    rv2 = log(R2)   # in rotation vector

    # t is repeatedly increasing from 0.0 to 1.0
    t = (ang % 90) / 90.

    M = np.identity(4)

    # slerp
    if gVisibles[0]:
        R = slerp(R1, R2, t)
        glPushMatrix()
        M[:3,:3] = R
        glMultMatrixf(M.T)
        drawCubes(1.)
        glPopMatrix()

    # interpolation between rotation vectors
    if gVisibles[1]:
        R = interpolateRotVec(rv1, rv2, t)
        glPushMatrix()
        M[:3,:3] = R
        glMultMatrixf(M.T)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (0.,1.,0.,1.))
        drawCubes(.75)
        glPopMatrix()

    # interpolation between Euler angles
    if gVisibles[2]:
        R = interpolateZYXEuler(euler1, euler2, t)
        glPushMatrix()
        M[:3,:3] = R
        glMultMatrixf(M.T)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (0.,0.,1.,1.))
        drawCubes(.5)
        glPopMatrix()

    # interpolation between rotation matrices
    if gVisibles[3]:
        R = interpolateRotMat(R1, R2, t)
        glPushMatrix()
        M[:3,:3] = R
        glMultMatrixf(M.T)
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (0.,0.,1.,1.))
        drawCubes(.25)
        glPopMatrix()

    glDisable(GL_LIGHTING)


def key_callback(window, key, scancode, action, mods):
    global gCamAng, gCamHeight
    global gVisibles
    # rotate the camera when 1 or 3 key is pressed or repeated
    if action==glfw.PRESS or action==glfw.REPEAT:
        if key==glfw.KEY_1:
            gCamAng += np.radians(-10)
        elif key==glfw.KEY_3:
            gCamAng += np.radians(10)
        elif key==glfw.KEY_2:
            gCamHeight += .1
        elif key==glfw.KEY_W:
            gCamHeight += -.1
        elif key==glfw.KEY_A:
            gVisibles[0] = not gVisibles[0]
        elif key==glfw.KEY_S:
            gVisibles[1] = not gVisibles[1]
        elif key==glfw.KEY_D:
            gVisibles[2] = not gVisibles[2]
        elif key==glfw.KEY_F:
            gVisibles[3] = not gVisibles[3]
        elif key==glfw.KEY_Z:
            gVisibles[:] = [False]*4
        elif key==glfw.KEY_X:
            gVisibles[:] = [True]*4

gVertexArraySeparate = None
def main():
    global gVertexArraySeparate

    if not glfw.init():
        return
    window = glfw.create_window(480,480,'2018008331-10-1', None,None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)
    glfw.set_key_callback(window, key_callback)
    glfw.swap_interval(1)

    # ...
    gVertexArraySeparate = createVertexArraySeparate()

    count = 0
    while not glfw.window_should_close(window):
        glfw.poll_events()
        ang = count % 360
        render(ang)
        count += 1
        glfw.swap_buffers(window)

    glfw.terminate()

if __name__ == "__main__":
    main()


