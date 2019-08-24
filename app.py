import log_res as lr
import requests
from flask import Flask, render_template,request

app = Flask(__name__)
@app.route('/')
def home():
    return render_template('index.html')

@app.route('/predict-star',methods=['GET','POST'])
def predict_star():
    
    if request.method == 'POST':
        mip = float(request.form['mip'])
        stdip = float(request.form['stdip'])
        skip = float(request.form['skip'])
        ekip = float(request.form['ekip'])
        mdmsnr = float(request.form['mdmsnr'])
        stddmsnr = float(request.form['stddmsnr'])
        ekdmsnr = float(request.form['ekdmsnr'])
        skdmsnr = float(request.form['skdmsnr'])
        x = [mip,stdip,ekip,skip,mdmsnr,stddmsnr,ekdmsnr,skdmsnr]
        y = model.predict(x)
        if y == 0:
            pred = "Pulsar Star"
        else:
            pred = "Not Pulsar Star"
        print(pred)
    
    return render_template("index.html",pred=pred)

model = lr.LogisticRegression()

if __name__ == '__main__':
    app.run()
