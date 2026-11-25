from PIL import Image, ImageDraw, ImageFont
from pathlib import Path
P=Path('/mnt/data/rup_work')
FONT='/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf'
BOLD='/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf'
NAVY=(51,65,85); FILL=(243,246,251); CANCEL=(255,247,237); TEXT=(20,30,43); WHITE=(255,255,255)

def f(size,b=False): return ImageFont.truetype(BOLD if b else FONT,size)
def centered(draw,xy,text,font,fill=TEXT,spacing=6):
    draw.multiline_text(xy,text,font=font,fill=fill,anchor='mm',align='center',spacing=spacing)
def arrow(draw, a,b, width=7, color=NAVY, head=22):
    draw.line([a,b],fill=color,width=width)
    import math
    ang=math.atan2(b[1]-a[1],b[0]-a[0])
    p1=(b[0]-head*math.cos(ang)+head*.55*math.sin(ang), b[1]-head*math.sin(ang)-head*.55*math.cos(ang))
    p2=(b[0]-head*math.cos(ang)-head*.55*math.sin(ang), b[1]-head*math.sin(ang)+head*.55*math.cos(ang))
    draw.polygon([b,p1,p2],fill=color)
def node(draw,box,label,cancel=False,font_size=42):
    draw.rounded_rectangle(box,radius=35,fill=CANCEL if cancel else FILL,outline=NAVY,width=6)
    centered(draw,((box[0]+box[2])//2,(box[1]+box[3])//2),label,f(font_size),TEXT)

# Portrait version for report
W,H=1600,2100
im=Image.new('RGB',(W,H),WHITE); d=ImageDraw.Draw(im)
main=(180,170,800,330); wait=(180,520,800,680); paid=(180,830,800,990); packing=(180,1140,800,1300); sent=(180,1450,800,1610); delivered=(180,1760,800,1920); cancel=(1000,520,1540,680)
node(d,main,'Создан'); node(d,wait,'Ожидает оплаты'); node(d,paid,'Оплачен'); node(d,packing,'Собирается'); node(d,sent,'Отправлен'); node(d,delivered,'Доставлен'); node(d,cancel,'Отменён',True)
# initial pseudostate
cx=490; d.ellipse((cx-20,75,cx+20,115),fill=TEXT); arrow(d,(cx,115),(cx,170))
labels=[('подтвердить',main,wait),('оплата получена',wait,paid),('передать в сборку',paid,packing),('передать перевозчику',packing,sent),('доставка подтверждена',sent,delivered)]
for label,src,dst in labels:
    x=(src[0]+src[2])//2; y1=src[3]; y2=dst[1]
    arrow(d,(x,y1),(x,y2))
    centered(d,(x,(y1+y2)//2),label,f(30),TEXT)
# branch cancellation arrow and label above it
arrow(d,(wait[2],600),(cancel[0],600))
centered(d,((wait[2]+cancel[0])//2,548),'срок истёк\n[оплаты нет]',f(27),TEXT)
im.save(P/'order_states.png')

# Landscape version for presentation: transition labels sit above the states, not on top of them.
W,H=3200,1000
im=Image.new('RGB',(W,H),WHITE); d=ImageDraw.Draw(im)
xs=[150,660,1170,1680,2190,2700]
labels=['Создан','Ожидает оплаты','Оплачен','Собирается','Отправлен','Доставлен']
boxes=[]
for x,label in zip(xs,labels):
    box=(x,300,x+350,480); boxes.append(box); node(d,box,label,font_size=39)
# initial dot and arrow
cx=75; d.ellipse((cx-17,373,cx+17,407),fill=TEXT); arrow(d,(cx+18,390),(xs[0],390),width=6,head=20)
trans=['подтвердить','оплата получена','передать в сборку','передать перевозчику','доставка подтверждена']
for i,label in enumerate(trans):
    a=boxes[i]; b=boxes[i+1]; y=390
    arrow(d,(a[2],y),(b[0],y),width=6,head=20)
    centered(d,((a[2]+b[0])//2,235),label,f(27),TEXT)
# cancellation branch from waiting state
cbox=(660,700,1010,880); node(d,cbox,'Отменён',True,font_size=39)
arrow(d,((boxes[1][0]+boxes[1][2])//2,boxes[1][3]),((cbox[0]+cbox[2])//2,cbox[1]),width=6,head=20)
centered(d,((cbox[0]+cbox[2])//2,590),'срок истёк\n[оплаты нет]',f(28),TEXT)
im.save(P/'order_states_report.png')
