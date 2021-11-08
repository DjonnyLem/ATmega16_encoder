#https://python-scripts.com/tkinter

import os
import datetime
import tkinter as tk
from tkinter import ttk

years = (2018,2019,2020,2021,2022,2023,2024,2025,2026,2027,2028,2029,2030,2031,2032,2033,2034,2035,2036,2037,2038,2039,2040,2041,2042,2043,2044,2045,2046,2047,2048,2049,2050)
months = ('Январь','Февраль','Март','Апрель','Май','Июнь','Июль','Август','Сентябрь','Октябрь','Ноябрь','Декабрь')
days =(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31)

 
def make_dir():
    a = int(months.index(cmb_month.get())) +1
    b = int(cmb_first_day.get())
    c = int(cmb_last_day.get()) + 1
    d = int(cmb_year.get())

    for i in range (b, c):
        if i < 10:
                if a < 10:
                    os.mkdir(str(d)+ '.' + '0' + str(a) + '.0' + str(i))
                else:
                    os.mkdir(str(d)+ '.' + str(a) + '.0' + str(i))
        else:
            if a < 10:
                os.mkdir(str(d)+ '.' + '0' + str(a) + '.' + str(i))
            else:
                os.mkdir(str(d)+ '.' + str(a) + '.' + str(i))

                
def lbl_style(txt,row,column):
    return tk.Label(win, text=txt, foreground="#404040",font=20).grid(row=row,column=column,padx=3, pady=3,sticky="e")

def cmb_style(values,row,column):
    d=datetime.date.today()

    if values == years:
        dd = years.index(d.year)
    elif values == months:
        dd = d.month-1
    elif values == days:
        dd = days.index(d.day)    

    cmb = ttk.Combobox(win,values=values,font=20,foreground="#404040")
    cmb.current(dd)
    cmb.grid(row=row,column=column,padx=15, pady=3,sticky="we")
    return cmb
win = tk.Tk()
win.title('Программа для создания папок')
win.geometry("500x250")
win.resizable(width=False, height=False)
win.columnconfigure([0,1], weight=1, minsize=75)
win.rowconfigure([0,6], weight=1, minsize=50)
 
lbl = tk.Label(win, text="Программа создает папки с наименованием в формате DD.MM.YY.\n Месяц и период дней введите в форме ниже.", foreground="grey20")
lbl.grid(row=0,columnspan=2, sticky="we",padx=3, pady=3)


lbl_year=lbl_style("Выберите год:",1,0)
cmb_year = cmb_style(years,1,1)


lbl_month=lbl_style("Выберите месяц:",2,0)
cmb_month = cmb_style(months,2,1)


lbl_first_day = lbl_style("Выберите начальную дату:",3,0)
cmb_first_day = cmb_style(days,3,1)

lbl_last_day = lbl_style("Выберите конечную дату:",4,0)
cmb_last_day = cmb_style(days,4,1)


lbl = tk.Label(win, text="Куда сохранить результат", foreground="grey20")
lbl.grid(row=5,columnspan=2, sticky="we",padx=3, pady=3)

frame_button = tk.Frame(win,)
frame_button.grid(row=6,columnspan=2, sticky="we",padx=3, pady=3)

button = tk.Button(frame_button, text="Создать папки", width=14, height=2, fg="grey22",command=make_dir)
button.pack(side=tk.RIGHT,fill=tk.BOTH, padx=15, pady=5)


win.mainloop()
'''

import tkinter as tk
import tkinter.filedialog as fd

class App(tk.Tk):
    def __init__(self):
        super().__init__()
        btn_file = tk.Button(self, text="Выбрать файл",
                             command=self.choose_file)
        btn_dir = tk.Button(self, text="Выбрать папку",
                             command=self.choose_directory)
        btn_file.pack(padx=60, pady=10)
        btn_dir.pack(padx=60, pady=10)

    def choose_file(self):
        filetypes = (("Текстовый файл", "*.txt"),
                     ("Изображение", "*.jpg *.gif *.png"),
                     ("Любой", "*"))
        filename = fd.askopenfilename(title="Открыть файл", initialdir="/",
                                      filetypes=filetypes)
        if filename:
            print(filename)

    def choose_directory(self):
        directory = fd.askdirectory(title="Открыть папку", initialdir="/")
        if directory:
            print(directory)

if __name__ == "__main__":
    app = App()
    app.mainloop()

'''
