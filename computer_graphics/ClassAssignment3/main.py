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

fovy = 60

flag_left_press = False
flag_right_press = False

filePath = None

root_pos = None
root_pos_col = None
adj_list=[[]]
joint_info = [0]
motion_data = []
frame_num = 0
FPS = 1
motion_flag = 0
frame_cnt = 0
frame_time = 1

class joint:
    def __init__(self, name, off_pos, euler_angle, column, is_root):
        self.name = name
        self.off_pos = off_pos
        self.euler_angle = euler_angle
        self.column = column
        self.is_root = is_root
        self.pos = None
        self.rotate_angle = None

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
    for i in range(-7,8):
        glVertex3fv(np.array([i,0,7]))
        glVertex3fv(np.array([i,0,-7]))
        glVertex3fv(np.array([7,0,i]))
        glVertex3fv(np.array([-7,0,i]))
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
    global motion_flag
    if action==glfw.PRESS or action==glfw.REPEAT:
        if key==glfw.KEY_SPACE:
            motion_flag = 1
            
def drop_callback(window, paths):
    global filePath
    global adj_list, joint_info, root_pos, root_pos_col, motion_data
    global frame_num, FPS, motion_flag, frame_cnt, frame_time
    
    adj_list=[[]]
    joint_info = [0]
    root_pos = None
    root_pos_col = None
    motion_data = []
    frame_num = 0
    FPS = 1
    motion_flag = 0
    frame_cnt = 0
    frame_time = 1

    filePath = paths[0]
    f = open(filePath, 'r')
    lines = f.readlines()

    section = 0
    name = None
    stack = [0]
    is_root_stack = []
    cnt_joint = 0
    col_num = 0
    col_stack = []
    off_stack = []
    euler_stack = []
    column = []
    is_root = 0
    joint_num = 0
    joint_names = []

    for line in lines:
        l = line[:-1]
        l = l.replace('\t',' ')
        val = l.split(' ')
        val = [x for x in val if x]
        if line == 'HIERARCHY\n':
            section = 0
            continue
        elif line == 'MOTION\n':
            section = 1
            continue
        elif val[0] == '{':
            stack.append(cnt_joint)
            adj_list.append([])
            joint_info.append(None)
            column = []
            continue
        elif val[0] == '}':
            curr = stack.pop()
            top = stack[-1]
            adj_list[top].append(curr)
            is_root = is_root_stack.pop()
            offset = off_stack.pop()
            euler = None
            if joint_names[curr-1] != 'end_site':
                column = col_stack.pop()
                euler = euler_stack.pop()
            joint_info[curr] = joint(joint_names[curr-1], offset, euler, column, is_root)
            continue

        # parse hierarchy section
        if section == 0:
            if val[0] == 'ROOT':
                name = val[1]
                joint_num += 1
                cnt_joint += 1
                joint_names.append(name)
                is_root = 1
                is_root_stack.append(is_root)
            elif val[0] == 'OFFSET':
                offset = np.array([val[1], val[2], val[3]], 'float32')
                off_stack.append(offset)
            elif val[0] == 'CHANNELS':
                if is_root == 1:
                    root_pos = [val[2][0], val[3][0], val[4][0]]
                    root_pos_col = [col_num, col_num+1, col_num+2]
                    col_num += 3
                    euler = [val[5][0], val[6][0], val[7][0]]
                else:
                    euler = [val[2][0], val[3][0], val[4][0]]
                column.append(col_num)
                column.append(col_num+1)
                column.append(col_num+2)
                col_num += 3
                col_stack.append(column)
                euler_stack.append(euler)
            elif val[0] == 'JOINT':
                 name = val[1]
                 joint_names.append(name)
                 joint_num += 1
                 cnt_joint += 1
                 is_root = 0
                 is_root_stack.append(is_root)
            elif val[0] == 'End':
                name = 'end_site'
                joint_names.append(name)
                cnt_joint += 1
                is_root = 0
                is_root_stack.append(is_root)

        else:
            if val[0] == 'Frames:':
                frame_num = (int)(val[1])
                continue
            elif val[0] == 'Frame':
                FPS = 1.0/(float)(val[2])
                frame_time = (float)(val[2])
                continue
            values = []
            for v in val:
                values.append((float)(v))
            motion_data.append(values)

    joint_names = [x for x in joint_names if x != 'end_site']

    print("1. File Name: ", filePath)
    print("2. Number of Frames: ", frame_num)
    print("3. FPS: ", FPS)
    print("4. Number of Joints: ", joint_num)
    print("5. List of Joint Names", joint_names)
    
def search(curr, pre_pos, mat):
    global adj_list, joint_info, motion_flag, frame_cnt
    
    curr_pos = pre_pos @ mat[:3,:3] + np.array(joint_info[curr].off_pos)
    glBegin(GL_LINES)
    glColor3ub(255, 255, 0)
    glVertex3fv(pre_pos @ mat[:3,:3])
    glVertex3fv(curr_pos)
    glEnd()

    glPushMatrix()
    M = np.identity(4,'float32')
    if motion_flag == 1:
        if joint_info[curr].euler_angle != None:
            euler = np.array([motion_data[frame_cnt][joint_info[curr].column[0]],
                              motion_data[frame_cnt][joint_info[curr].column[1]],
                              motion_data[frame_cnt][joint_info[curr].column[2]]])
            euler = np.radians(euler)
        if joint_info[curr].euler_angle == ['Z', 'X', 'Y']:
            M = ZXYEulerToRotMat(euler)
        elif joint_info[curr].euler_angle == ['Z', 'Y', 'X']:
            M = ZYXEulerToRotMat(euler)
        elif joint_info[curr].euler_angle == ['Y', 'X', 'Z']:
            M = YXZEulerToRotMat(euler)
        elif joint_info[curr].euler_angle == ['Y', 'Z', 'X']:
            M = YZXEulerToRotMat(euler)
        elif joint_info[curr].euler_angle == ['X', 'Y', 'Z']:
            M = XYZEulerToRotMat(euler)
        elif joint_info[curr].euler_angle == ['X', 'Z', 'Y']:
            M = XZYEulerToRotMat(np.radians(euler))
        
        glMultMatrixf(M.T) 

    for x in adj_list[curr]:
        search(x, curr_pos, M)
    
    glPopMatrix()


def XYZEulerToRotMat(euler):
    xang, yang, zang = euler
    Rx = np.array([[1,0,0,0],
                   [0, np.cos(xang), -np.sin(xang), 0],
                   [0, np.sin(xang), np.cos(xang), 0],
                   [0,0,0,1]])
    Ry = np.array([[np.cos(yang), 0, np.sin(yang), 0],
                   [0,1,0,0],
                   [-np.sin(yang), 0, np.cos(yang), 0],
                   [0,0,0,1]])
    Rz = np.array([[np.cos(zang), -np.sin(zang), 0, 0],
                   [np.sin(zang), np.cos(zang), 0, 0],
                   [0,0,1,0],
                   [0,0,0,1]])
    return Rx @ Ry @ Rz

def XZYEulerToRotMat(euler):
    xang, zang, yang = euler
    Rx = np.array([[1,0,0,0],
                   [0, np.cos(xang), -np.sin(xang), 0],
                   [0, np.sin(xang), np.cos(xang), 0],
                   [0,0,0,1]])
    Ry = np.array([[np.cos(yang), 0, np.sin(yang), 0],
                   [0,1,0,0],
                   [-np.sin(yang), 0, np.cos(yang), 0],
                   [0,0,0,1]])
    Rz = np.array([[np.cos(zang), -np.sin(zang), 0, 0],
                   [np.sin(zang), np.cos(zang), 0, 0],
                   [0,0,1,0],
                   [0,0,0,1]])
    return Rx @ Ry @ Rz

def YXZEulerToRotMat(euler):
    yang, xang, zang = euler
    Rx = np.array([[1,0,0,0],
                   [0, np.cos(xang), -np.sin(xang), 0],
                   [0, np.sin(xang), np.cos(xang), 0],
                   [0,0,0,1]])
    Ry = np.array([[np.cos(yang), 0, np.sin(yang), 0],
                   [0,1,0,0],
                   [-np.sin(yang), 0, np.cos(yang), 0],
                   [0,0,0,1]])
    Rz = np.array([[np.cos(zang), -np.sin(zang), 0, 0],
                   [np.sin(zang), np.cos(zang), 0, 0],
                   [0,0,1,0],
                   [0,0,0,1]])
    return Ry @ Rx @ Rz

def YZXEulerToRotMat(euler):
    yang, zang, xang = euler
    Rx = np.array([[1,0,0,0],
                   [0, np.cos(xang), -np.sin(xang), 0],
                   [0, np.sin(xang), np.cos(xang), 0],
                   [0,0,0,1]])
    Ry = np.array([[np.cos(yang), 0, np.sin(yang), 0],
                   [0,1,0,0],
                   [-np.sin(yang), 0, np.cos(yang), 0],
                   [0,0,0,1]])
    Rz = np.array([[np.cos(zang), -np.sin(zang), 0, 0],
                   [np.sin(zang), np.cos(zang), 0, 0],
                   [0,0,1,0],
                   [0,0,0,1]])
    return Ry @ Rz @ Rx

def ZXYEulerToRotMat(euler):
    zang, xang, yang = euler
    Rx = np.array([[1,0,0,0],
                   [0, np.cos(xang), -np.sin(xang), 0],
                   [0, np.sin(xang), np.cos(xang), 0],
                   [0,0,0,1]])
    Ry = np.array([[np.cos(yang), 0, np.sin(yang), 0],
                   [0,1,0,0],
                   [-np.sin(yang), 0, np.cos(yang), 0],
                   [0,0,0,1]])
    Rz = np.array([[np.cos(zang), -np.sin(zang), 0, 0],
                   [np.sin(zang), np.cos(zang), 0, 0],
                   [0,0,1,0],
                   [0,0,0,1]])
    return Rz @ Rx @ Ry

def ZYXEulerToRotMat(euler):
    zang, yang, xang = euler
    Rx = np.array([[1,0,0,0],
                   [0, np.cos(xang), -np.sin(xang), 0],
                   [0, np.sin(xang), np.cos(xang), 0],
                   [0,0,0,1]])
    Ry = np.array([[np.cos(yang), 0, np.sin(yang), 0],
                   [0,1,0,0],
                   [-np.sin(yang), 0, np.cos(yang), 0],
                   [0,0,0,1]])
    Rz = np.array([[np.cos(zang), -np.sin(zang), 0, 0],
                   [np.sin(zang), np.cos(zang), 0, 0],
                   [0,0,1,0],
                   [0,0,0,1]])
    return Rz @ Ry @ Rx


def render():
    global M, frame_cnt
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)     
    glEnable(GL_DEPTH_TEST)     
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE )
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    
    gluPerspective(fovy, 1, 5, 1000)
    glTranslatef(0., 0., -300)

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    gluLookAt(.3, .3, 1, 0, 0, 0, 0., .1, 0)

    glTranslatef(x_translate/30, 0., 0.)
    glTranslatef(0., y_translate/30, 0.)
  
    glRotatef(y_rotate/3, 1., 0., 0.)
    glRotatef(x_rotate/3, 0., 1., 0.)
    
    drawFrame()
    drawXZ()

    if filePath == None:
        return

    I = np.identity(4)
    if motion_flag == 0:
        search(1, np.array([0,0,0]), I)
    else:
        par = ''
        par = par + root_pos[0] + root_pos[1] + root_pos[2]
        x = motion_data[frame_cnt][root_pos_col[0]]
        y = motion_data[frame_cnt][root_pos_col[1]]
        z = motion_data[frame_cnt][root_pos_col[2]]
        if par == 'XYZ':
            search(1, np.array([x,y,z]), I)
        elif par == 'XZY':
            search(1, np.array([x,z,y]), I)
        elif par == 'YXZ':
            search(1, np.array([y,x,z]), I)
        elif par == 'YZX':
            search(1, np.array([y,z,x]), I)
        elif par == 'ZXY':
            search(1, np.array([z,x,y]), I)
        elif par == 'ZYX':
            search(1, np.array([z,y,x]), I)

def main():
    global FPS, motion_flag, frame_cnt, frame_num, frame_time
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
        if motion_flag == 1:
            frame_cnt = (frame_cnt + 1) % frame_num
        glfw.swap_buffers(window)
    glfw.terminate()
    
if __name__ == "__main__":
    main()
