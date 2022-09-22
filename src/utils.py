def parse_string(stringa):
    array=stringa.split(",")
    data=[]
    lista_measurement=['Temperatura', 'Torbidita', "Residuo fisso", "pH"]
    lista_field_name=["Gradi", "Ntu", "ppm", "PH"]
    for i in range(0,len(array)):
        array[i]=float(array[i])
        data.append(parse_json(lista_measurement[i], lista_field_name[i], array[i]))
    return data
    
    


def parse_json(measurement, field_name, value):
    json = {
        'measurement' : measurement,
        'fields':  {
            field_name : value
        }
    }
    return json

