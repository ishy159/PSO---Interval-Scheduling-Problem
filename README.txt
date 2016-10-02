I. Hien thuc giai thuat Greedy cho bai toan Interval Scheduling
1. Khoi tao Bai toan:
Khoi tao bai toan voi
- MAX_TIME la khoang thoi gian de len lich.
- NUM_INTERVAL: so luong cac khoang con de sap xep vao khoang MAX_TIME tren.

Voi moi interval, khoi tao ngau nhien cac gia tri bat dau va ket thuc
(gia tri start < end, va nam trong khoang 0 -> MAX_TIME).
2. Mo hinh bai toan:
- Interval: luu thong tin ve 1 interval
- Node: luu cac thong tin ve cau truc.
Chung ta se co 1 node khoi dau. Sau khi, thuc hien sinh cac node con, chung se
cap nhat cac gia tri node cha cua no.
3. Luong gia bai toan:
Gia tri luong gia tai 1 node la gia tri cac khoang thoi gian con trong de dua
cac task khac vao.
Vd: MAX_TIME = 10, NUM_INTERVAL = 2.
Interval[0] = 1 -> 5, Interval[1] = 6 -> 7
Ta se co: Node *first; first->parent = NULL, first->current = Interval[0];
  => first->evalValue = MAX_TIME - (5 - 1) = 6
  Node *second; second->parent = first; second->current = Interval[1];
  => second->evalValue = MAX_TIME - (7 - 6) - first->evalValue = 5

Gia tri luong gia cang nho thi cang tot.(smaller is better.)
4. Chien luoc giai bai toan:
Bai toan duoc giai theo Greedy algorithm:
Trong qua trinh lua chon cac node ke tiep, giai thuat se uu tien lua chon nhung
node co gia tri (end - start) lon nhat ma thoa man dieu kien khong overlap
cac node cha cua no.
Cu tiep tuc nhu the toi khi nao khong the chen them node con duoc nua thi
dung lai.

II. Hien thuc PSO.
Reference
http://note.yuhc.me/2014/10/parallel-pso-algorithm/

Bai toan PSO duoc thuc hien lai de giai quyet van de, tim gia tri nho nhat cua
ham so z = x ^ 2 + y ^ 2 voi x va y trong khoang -100 -> 100.
Bai toan giai quyet de dang neu so luong Particle la rat lon (khoang 1000000).
Con neu nho hon thi co the bi lap vo han.
Minh van chua giai quyet dc van de nay, nhung ve nguyen ly hoat dong cua PSO thi
ok.
