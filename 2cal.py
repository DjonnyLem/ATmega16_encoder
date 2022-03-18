import datetime, calendar, locale
from tkinter import *


class Window:
    def __init__(self):
        self.root = Tk()
        self.root.title("Calendar")
        self.root.geometry("400x400")
        self.root.resizable(width=False, height=False)

    def run(self):
        self.draw_widgets()
        self.root.mainloop()


    def btn_days_of_month (self,frame,name,row,column):
        if name == 0:
             name= ""
        self.button_select = Button(frame,
                               text=name,
                               width=1,
                               height=1,
                               command=lambda n=name: self.btn_push(n),
                               activebackground="lightgreen",
                               fg="#404040")
        self.button_select.grid(row=row,column=column, sticky="we",padx=1, pady=1)
        



    
    

    def btn_push(self,n):
        self.button_select.configure(font=24,fg="red",bg="red")
        print(n)
        print(set(self.button_select.configure()))
        #print(dir(self.button_select))

    def draw_widgets(self):
        
        week_list=calendar.Calendar().monthdays2calendar(2022, 3)

        
        # Создание фрейма для кнопок дней месяца   
        frame_days = Frame(self.root, bg="lightblue")
        frame_days.grid(row=2, column=1,sticky="we",padx=2, pady=2)

     


        # Создание кнопок дней месяца
        for num_weeks,i in enumerate (week_list):
             for day, num_day in i:
                 self.btn_days_of_month (frame_days,day,num_weeks,num_day)

      
        
    


if __name__ == "__main__":
    window = Window()
    window.run()
    


