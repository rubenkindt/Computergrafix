%----------------Gegevens-----------------
P1=[1; 1; 1; 1];
P2=[2;-1 ;1; 1];
breedte=500;
hoogte=500;
    %stand camera
x=0.0;
y=2.0;
z=5.0;
    %PC
    xwmin=-1.5;
    xwmax=2.5;
    ywmin=-2.0;
    ywmax=2.0;
    near=1.0;
    far=12.0;
  

%---------------WC naar VC----------------

T=[1 0 0 -x;
   0 1 0 -y;
   0 0 1 -z;
   0 0 0 1]
theta = atan(y/z);

R=[1 0 0 0;
   0 cos(theta) -sin(theta) 0;
   0 -sin(theta) -cos(theta) 0;
   0 0 0 1]

M_WC_VC = R*T %T*R 
%-----------------VC naar PC-------------------
sz=(near+far)/(near-far);
tz=-(2*near*far)/(near-far);

M_VC_PC=[-near 0 0 0;
    0 -near 0 0;
    0 0 sz tz;
    0 0 -1 0]
%-----------------VC naar NC-------------------
x1=-(2*near)/(xwmax-xwmin);
x2=(xwmax+xwmin)/(xwmax-xwmin);
y1=-(2*near)/(ywmax-ywmin);
y2=(ywmax+ywmin)/(ywmax-ywmin);
M_VC_NC=[x1 0 x2 0;
         0 y1 y2 0;
         0 0 sz tz;
         0 0 -1 0]
%-----------------NC naar DC--------------------
sx=breedte/2;
tx=breedte/2;
sy=hoogte/2;
ty=hoogte/2; %????

M_NC_DC=[sx 0 tx;
        0 sy ty;
        0 0 1]
%-----------Berekening voor punt P1-------------
P1res1VC=M_WC_VC*P1
P1res2NC=M_VC_NC*P1res1
tussen= P1res2([1 2 4]) %(de zmoet er uit)
P1res3DC=M_NC_DC*tussen
%-----------Berekening voor punt P2--------------
P2res1VC=M_WC_VC*P2
P2res2NC=M_VC_NC*P2res1
tussen2= P2res2([1 2 4]) %(de zmoet er uit)
P2res3DC=M_NC_DC*tussen2
%-----welk punt ligt het dichtste (z coord)------

if (P1res2NC([3]) > P2res2NC([3]))
   "P1 ligt dichter bij"                %klopt dit????
   disp(P1res2NC([3]));
   disp(P2res2NC([3]));
else
    WelkPuntLigtDichter="P2 light dichter bij" 
    disp(P1res2NC([3]));
    disp(P2res2NC([3]));
end


if ((P1res2NC([3])/P1res2NC([4])) > (P2res2NC([3])/P2res2NC([4])))
   "P1 ligt dichter bij"                % of is dit juister???
   disp(P1res2NC([3]));
   disp(P2res2NC([3]));
else
    WelkPuntLigtDichter="P2 light dichter bij" 
    disp(P1res2NC([3]));
    disp(P2res2NC([3]));
end
