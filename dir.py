#https://python-scripts.com/tkinter
import tkinter as tk

window = tk.Tk()
window.title('Программа создания папок')
window.geometry("550x250")

frame = tk.Frame() 
frame.pack(fill=tk.X, side=tk.TOP)

label = tk.Label(
        master=frame,
        text="Программа создает папки с наименованием в формате DD.MM.YY.\n Месяц и период дней введите в форме ниже.",
        foreground="grey20")
label.pack( padx=5, pady=15)

frame1 = tk.Frame()
frame1.pack(fill=tk.BOTH, side=tk.LEFT, expand=True, padx=5, pady=5)



frame_mount = tk.Frame(master=frame1)
frame_mount.pack(fill=tk.X)#(fill=tk.BOTH, side=tk.LEFT, expand=True)

lbl_mount = tk.Label(frame_mount, text="Введите месяц:", foreground="grey20",font=50)
lbl_mount.pack(side=tk.LEFT, padx=5, pady=5)

entry_mount = tk.Entry(frame_mount, fg="grey20", bg="grey98", width=40, font=50)
entry_mount.pack(fill=tk.X, padx=5, expand=True)



frame_first_day = tk.Frame(master=frame1)
frame_first_day.pack(fill=tk.X)

lbl_first_day = tk.Label(master=frame_first_day, text="Введите начальную дату:", foreground="grey20")
lbl_first_day.pack(side=tk.LEFT, padx=5, pady=5)

entry__first_day = tk.Entry(master=frame_first_day, fg="grey20", bg="grey98", width=40)
entry__first_day.pack(fill=tk.X, padx=5, expand=True)



frame_last_day = tk.Frame(master=frame1)
frame_last_day.pack(fill=tk.X)

lbl_last_day = tk.Label(master=frame_last_day, text="Введите конечную дату:", foreground="grey20")
lbl_last_day.pack(side=tk.LEFT, padx=5, pady=5)

entry_last_day = tk.Entry(master=frame_last_day, fg="grey20", bg="grey98", width=40)
entry_last_day.pack(fill=tk.X, padx=5, expand=True)



frame_button = tk.Frame(master=frame1)
frame_button.pack(fill=tk.X)

button = tk.Button(master=frame_button, text="Создать папки", width=14, height=2, fg="grey22")
button.pack(side=tk.RIGHT,fill=tk.BOTH, padx=5, pady=5)





window.mainloop()



'''
from tkinter import Tk, Text, BOTH, X, N, LEFT
from tkinter.ttk import Frame, Label, Entry
 
 
class Example(Frame):
 
    def __init__(self):
        super().__init__()
        self.initUI()
 
    def initUI(self):
        self.master.title("Оставить отзыв")
        self.pack(fill=BOTH, expand=True)
 
        frame1 = Frame(self)
        frame1.pack(fill=X)
 
        lbl1 = Label(frame1, text="Заголовок", width=10)
        lbl1.pack(side=LEFT, padx=5, pady=5)
 
        entry1 = Entry(frame1)
        entry1.pack(fill=X, padx=5, expand=True)
 
        frame2 = Frame(self)
        frame2.pack(fill=X)
 
        lbl2 = Label(frame2, text="Автор", width=10)
        lbl2.pack(side=LEFT, padx=5, pady=5)
 
        entry2 = Entry(frame2)
        entry2.pack(fill=X, padx=5, expand=True)
 
        frame3 = Frame(self)
        frame3.pack(fill=BOTH, expand=True)
 
        lbl3 = Label(frame3, text="Отзыв", width=10)
        lbl3.pack(side=LEFT, anchor=N, padx=5, pady=5)
 
        txt = Text(frame3)
        txt.pack(fill=BOTH, pady=5, padx=5, expand=True)
 
 
def main():
 
    root = Tk()
    root.geometry("300x300+300+300")
    app = Example()
    root.mainloop()
 
 
if __name__ == '__main__':
    main()



'''
