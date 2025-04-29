import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/claudia-elez/Desktop/asoftwarer/pfinal/final_project_arquitectura/install/yolo_ros'
