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

fovy = 15

flag_left_press = False
flag_right_press = False

filePath = None
gVertexArraySeparate = None
gVertexArraySeparate_smooth = None

vertexArr = np.array([[]], 'float32')
indexArr = np.array([[]],'int32')
normalArr = np.array([[]],'float32')
faceArr = np.array([[[]]])

varrO = np.array([[]], 'float32')
fNormalArr = np.array([[]], 'float32')
vNormalArr = np.array([[]], 'float32')

vertexEach = []

shading_mode = GL_LINE
face_mode = True

def drawFrame():
    glBegin(GL_LINES)
    glColor3ub(255, 0, 0)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([3.,0.,0.]))
    glColor3ub(0, 255, 0)
    glVertex3fv(np.array([0.,0.,0.]))
    glVertex3fv(np.array([0.,3.,0.]))
    glColor3ub(0, 0, 255)
    glVertex3fv(np.array([0.,0.,0]))
    glVertex3fv(np.array([0.,0.,3.]))
    glEnd()

def drawXZ():
    glBegin(GL_LINES)
    glColor3ub(255, 255, 255)
    for i in range(-10,11):
        glVertex3fv(np.array([i,0,10]))
        glVertex3fv(np.array([i,0,-10]))
        glVertex3fv(np.array([10,0,i]))
        glVertex3fv(np.array([-10,0,i]))
    glEnd()

def button_callback(window, button, action, mod):
    global flag_left_press, flag_right_press
    global scene_x, scene_y
    if button == glfw.MOUSE_BUTTON_LEFT:
        if action == glfw.PRESS or action == glfw.REPEAT:
            flag_left_press = True
            scene_x, scene_y = glfw.get_cursor_pos(window)
        elif action == glfw.RELEASE:
            flag_left_press = False
    elif button == glfw.MOUSE_BUTTON_RIGHT:
        if action == glfw.PRESS or action == glfw.REPEAT:
            flag_right_press = True
            scene_x, scene_y = glfw.get_cursor_pos(window)
        elif action == glfw.RELEASE:
            flag_right_press = False

def cursor_callback(window, xpos, ypos):
    global x_rotate, y_rotate
    global x_translate, y_translate
    global scene_x, scene_y
    if flag_left_press == True:
        x_rotate += xpos - scene_x
        y_rotate += ypos - scene_y
    elif flag_right_press == True:
        x_translate += xpos - scene_x
        y_translate -= ypos - scene_y
    scene_x = xpos
    scene_y = ypos

def scroll_callback(window, x, y):
    global fovy
    fovy -= y

def key_callback(window, key, scancode, action, mods):
    global shading_mode, face_mode
    if action==glfw.PRESS or action==glfw.REPEAT:
        if key==glfw.KEY_Z:
            if shading_mode == GL_LINE:
                shading_mode = GL_FILL
            else:
                shading_mode = GL_LINE
        elif key==glfw.KEY_S:
            face_mode = not face_mode
            
def drop_callback(window, paths):
    global filePath
    global vertexArr, normalArr, faceArr, indexArr
    global gVertexArraySeparate, gVertexArraySeparate_smooth
    global shading_mode, face_mode, vertexEach
    shading_mode = GL_FILL
    face_mode = True
    gVertexArraySeparate = None
    gVertexArraySeparate_smooth = None
    face3 = face4 = faceOver4 = 0
    vertexEach = []

    vertexArr = np.array([[0,0,0]], 'float32')
    indexArr = np.array([[0,0,0]],'int32')
    normalArr = np.array([[0,0,0]],'float32')
    faceArr = np.array([[[0,0,0],[0,0,0],[0,0,0]]])

    filePath = paths[0]
    file = open(filePath, 'r')
    lines = file.readlines()

    for line in lines:
        data = line.split( )
        if line.startswith('#'):
            continue
        if not data:
            continue

        if data[0] == 'v':
            tmp_v = np.array([[float(data[1]), float(data[2]), float(data[3])]], 'float64')
            vertexArr = np.append(vertexArr, tmp_v, 0)
            vertexEach.append([])
            
        elif data[0] == "vn":
            tmp_vn = np.array([[float(data[1]), float(data[2]), float(data[3])]], 'float64')
            normalArr = np.append(normalArr, tmp_vn, 0)
            
        elif data[0] == 'f':
            if len(data) == 4:
                face3 += 1
            elif len(data) == 5:
                face4 += 1
            elif len(data) > 5:
                faceOver4 += 1
            vt1 = data[1].split('/')
            vt2 = data[2].split('/')
            vt3 = data[3].split('/')

            while len(vt1) < 3:
                vt1.append(0)
            while len(vt2) < 3:
                vt2.append(0)
            while len(vt3) < 3:
                vt3.append(0)
                
            for i in range(3):
                if vt1[i] == '':
                    vt1[i] = 0
                if vt2[i] == '':
                    vt2[i] = 0
                if vt3[i] == '':
                    vt3[i] = 0

            idx1 = int(vt1[0])-1
            idx2 = int(vt2[0])-1
            idx3 = int(vt3[0])-1
            idxTmp = np.array([[idx1, idx2, idx3]])
            
            vertexEach[idx1].append(len(indexArr)-1)
            vertexEach[idx2].append(len(indexArr)-1)
            vertexEach[idx3].append(len(indexArr)-1)
            
            tmp = np.array([[[idx1, int(vt1[1]), int(vt1[2])],
                             [idx2, int(vt2[1]), int(vt2[2])],
                             [idx3, int(vt3[1]), int(vt3[2])]]])
            faceArr = np.append(faceArr, tmp, 0)
            indexArr = np.append(indexArr, idxTmp, 0)

            num = 4
            lenTmp = len(data)

            while (lenTmp > 4):
                faceOver4 += 1
                vt2_2 = data[num-1].split('/')
                vt3_2 = data[num].split('/')
                while len(vt2_2) < 3:
                    vt2_2.append(0)
                while len(vt3_2) < 3:
                    vt3_2.append(0)
                for i in range(3):
                    if vt2_2[i] == '':
                        vt2_2[i] = 0
                    if vt3_2[i] == '':
                        vt3_2[i] = 0
                        
                idx2_2 = int(vt2_2[0])-1
                idx3_2 = int(vt3_2[0])-1
                idxTmp = np.array([[idx1, idx2_2, idx3_2]])

                vertexEach[idx1].append(len(indexArr)-1)
                vertexEach[idx2_2].append(len(indexArr)-1)
                vertexEach[idx3_2].append(len(indexArr)-1)
                
                tmp = np.array([[[idx1, int(vt1[1]), int(vt1[2])],
                                 [idx2_2, int(vt2_2[1]), int(vt2_2[2])],
                                 [idx3_2, int(vt3_2[1]), int(vt3_2[2])]]])
                faceArr = np.append(faceArr, tmp, 0)
                indexArr = np.append(indexArr, idxTmp, 0)

                num += 1
                lenTmp -= 1
            
    vertexArr = np.delete(vertexArr, 0, 0)
    normalArr = np.delete(normalArr, 0, 0)
    faceArr = np.delete(faceArr, 0, 0)
    indexArr = np.delete(indexArr, 0, 0)

    gVertexArraySeparate = gVertexArrayOr()
    gVertexArraySeparate_smooth = gVertexArraySm()

    print("\n1. File name : ", str(paths))
    print("2. Total number of faces : ", len(faceArr))
    print("3. Number of faces with 3 vertices : ", face3)
    print("4. Number of faces with 4 vertices : ", face4)
    print("5. Number of faces with more than 4 vertices : ", faceOver4)
    print()

def gVertexArrayOr():
    global face_mode
    global varrO
    global fNormalArr, vNormalArr
    varrO = np.array([[0,0,0]], 'float32')
    fNormalArr = np.array([[0,0,0]], 'float32')
    vNormalArr = np.array([[0,0,0]], 'float32')
    
    for i in range(len(faceArr)):
        v1 = vertexArr[faceArr[i][1][0]] - vertexArr[faceArr[i][0][0]]
        v2 = vertexArr[faceArr[i][2][0]] - vertexArr[faceArr[i][0][0]]
        n0 = n1 = n2 = np.cross(v1,v2)
        tmp = np.array([n0], 'float32')
        fNormalArr = np.append(fNormalArr, tmp, 0)
        if faceArr[i][0][2] != 0:
            n0 = normalArr[faceArr[i][0][2]-1]
            n1 = normalArr[faceArr[i][1][2]-1]
            n2 = normalArr[faceArr[i][2][2]-1]

        n0 = np.array([n0], 'float32')
        n1 = np.array([n1], 'float32')
        n2 = np.array([n2], 'float32')
        
        varrO = np.append(varrO, n0, 0)
        varrO = np.append(varrO, np.array([vertexArr[faceArr[i][0][0]]], 'float32'), 0)
        varrO = np.append(varrO, n1, 0)
        varrO = np.append(varrO, np.array([vertexArr[faceArr[i][1][0]]], 'float32'), 0)
        varrO = np.append(varrO, n2, 0)
        varrO = np.append(varrO, np.array([vertexArr[faceArr[i][2][0]]], 'float32'), 0)

    fNormalArr = np.delete(fNormalArr, 0, 0)
    varrO = np.delete(varrO, 0, 0)

    return varrO

def gVertexArraySm():
    global varrO
    global fNormalArr
    global vNormalArr
    varrS = np.array(varrO)
    
    for i in range(len(vertexArr)):
        sum = np.array([0,0,0], 'float32')
        for j in vertexEach[i]:
            sum += fNormalArr[j]
        if (vertexEach[i]):
            sum /= len(vertexEach[i])
        sum = np.array([sum])
        vNormalArr = np.append(vNormalArr, sum, 0)

    vNormalArr = np.delete(vNormalArr, 0, 0)
    for i in range(len(faceArr)):
        varrS[i*6] = vNormalArr[faceArr[i][0][0]]
        varrS[i*6 + 2] = vNormalArr[faceArr[i][1][0]]
        varrS[i*6 + 4] = vNormalArr[faceArr[i][2][0]]

    return varrS

def render():
    global face_mode
    global x_rotate, y_rotate
    global gVertexArraySeparate, gVertexArraySeparate_smooth
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)     
    glEnable(GL_DEPTH_TEST)     
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE )
    
    glLoadIdentity() 
    gluLookAt(.3, .3, 1, 0, 0, 0, 0., .1, 0)
	
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(fovy, 1, 10, 1000)
    glTranslatef(0., 0., -30)
    
    glMatrixMode(GL_MODELVIEW)
    glTranslatef(x_translate/30, 0., 0.)
    glTranslatef(0., y_translate/30, 0.)
  
    glRotatef(y_rotate/3, 1., 0., 0.)
    glRotatef(x_rotate/3, 0., 1., 0.)
    
    drawFrame()
    drawXZ()

    if filePath == None:
        return

    ########LIGHTING#######
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    glEnable(GL_LIGHT1)
    glEnable(GL_LIGHT2)
    glEnable(GL_LIGHT3)
    glEnable(GL_RESCALE_NORMAL)

    #light intensity for each channel
    #light0
    lightPos = (3.,4.,5.,1.)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos)
        
    lightColor = (1.,1.,0.,1.)
    ambientLightColor = (.1,.1,.1,1.)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor)
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightColor)

    #light1
    lightPos = (-3.,4.,-5.,1.)
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos)
        
    lightColor = (0.,1.,0.,1.)
    ambientLightColor = (.1,.1,.1,1.)
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor)
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor)
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLightColor)

    #light2
    lightPos = (-3.,-4.,5.,1.)
    glLightfv(GL_LIGHT2, GL_POSITION, lightPos)
        
    lightColor = (0.,1.,0.,1.)
    ambientLightColor = (.1,.1,.1,1.)
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColor)
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightColor)
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLightColor)

    #light3
    lightPos = (3.,-4.,-5.,1.)
    glLightfv(GL_LIGHT3, GL_POSITION, lightPos)
        
    lightColor = (0.,0.,1.,1.)
    ambientLightColor = (.1,.1,.1,1.)
    glLightfv(GL_LIGHT3, GL_DIFFUSE, lightColor)
    glLightfv(GL_LIGHT3, GL_SPECULAR, lightColor)
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLightColor)

    
    # material reflectance for each color channel
    objectColor = (1.,0.,0.,1.)
    specularObjectColor = (1.,1.,1.,1.)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, objectColor)
    glMaterialfv(GL_FRONT, GL_SHININESS, 10)
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularObjectColor)

    glPolygonMode(GL_FRONT, shading_mode)
    
    if face_mode == True:
        varr = gVertexArraySeparate
    else:
        varr = gVertexArraySeparate_smooth
    
    glEnableClientState(GL_VERTEX_ARRAY)
    glEnableClientState(GL_NORMAL_ARRAY)
    glNormalPointer(GL_FLOAT, 6*varr.itemsize, varr)
    glVertexPointer(3, GL_FLOAT, 6*varr.itemsize, ctypes.c_void_p(varr.ctypes.data + 3*varr.itemsize))
    glDrawArrays(GL_TRIANGLES, 0, int(varr.size/6))

    glDisable(GL_LIGHTING)

def main():
    if not glfw.init():
        return
    window = glfw.create_window(640, 640, "201800331", None, None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)
    glfw.set_cursor_pos_callback(window, cursor_callback)
    glfw.set_mouse_button_callback(window, button_callback)
    glfw.set_scroll_callback(window, scroll_callback)
    glfw.set_key_callback(window, key_callback)
    glfw.set_drop_callback(window, drop_callback)

    glfw.swap_interval(1)

    while not glfw.window_should_close(window):
        glfw.poll_events()
        render()
        glfw.swap_buffers(window)
    glfw.terminate()
    
if __name__ == "__main__":
    main()
