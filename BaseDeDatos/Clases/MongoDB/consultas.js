// QUERies QUE DESPLIEGA LAS ORDENES QUE PIDIERON PIZZAS QUE SON DE TAMAÑO MEDIANO

db.orders.find({size: "medium"}).pretty();

db.orders.aggregate({$match: {size: "medium"}}).pretty();

// QUERIES QUE DEPLIEGAN LAS PIZZAS QUE SON MEDIANAS 

db.orders.aggregate([{$match: {size: "medium"}}, {$group: {_id: "$name"}}]).pretty();

//QUERIES QUE DESPLIEGAN LAS GANANCIAS TOTALES DE LAS PIZZAS MEDIANAS SI SE VENDIERAN ORDENADAS POR EL TIPO DE PIZZA

db.orders.aggregate([{$match: {size: "medium"}}, {$group: {_id: "$name", montoTotal: {$sum: {$multiply: ["$price", "$quantity"]}}}}]).pretty();
db.orders.aggregate({$match: {size: "medium"}}, {$group: {_id: "$name", montoTotal: {$sum: {$multiply: ["$price", "$quantity"]}}}}).pretty();
