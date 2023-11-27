/** QUERY QUE MUESTRA LA CANTIDAD DE PELICULAS QUE TIENEN LOS PAÍSES QUE POSEAN ALGUNA PRODUCCIÓN  */

db.movies.aggregate(
    [
        {
            $match: {
                country: {$exists: true}
            }
        },

        {
            $group: {
                _id: "$country",
                cantidadPelis: {$sum: 1}
            }
        }
    ]
).pretty();

/** QUERY QUE MUESTRA LA CANTIDAD DE PELÍCULAS QUE  NO TIENEN PAÍS */

db.movies.aggregate(
    [
        {
            $match: {
                country: {$exists: false}
            }
        },

        {
            $group: {
                _id: "$country",
                pelis_sin_pais: {$sum: 1}
            }
        }
    ]
).pretty();

/** QUERY QUE MUESTRA EL NOMBRE DE LAS PIZZAS QUE SON GRANDES Y SU CANTIDAD EN STOCK  */

db.orders.aggregate(
    [
        {
            $match: {
                size: "large"
            }
        },
        {
            $group: {
                _id: "$name",
                cantidad: {$sum: "$quantity"}
            }
        }
    ]
).pretty();

/** QUERY QUE MUESTRA LOS ITEMS Y LA CANTIDAD QUE TIENEN DE DOCUMENTOS CADA ITEM */

db.sales.aggregate(
    {
        $group: {
            _id: "$item",
            cantidadDoc: {$sum: 1}
        }
    }
).pretty();

/** QUERY QUE DESPLIEGA LA CANTIDAD TOTAL DE CADA ITEM, O QUE SUMA TODOS LOS QUANTITIES PARA DAR UNO TOTAL */

db.sales.aggregate(
    {
        $group: {
            _id: "$item",
            cantidadTotal: {$sum: "$quantity"}
        }
    }
).pretty();

/** QUERY QUE DESPLIEGA LA VENTA TOTAL DEL ITEM abc */

db.sales.aggregate(
    [
        {
            $match:{item: "abc"}
        },

        {
            $group:{
                _id: "$item", 
                cantidadVendidaTotal: {
                    $sum:{
                        $multiply: ["$price", "$quantity"]
                    }
                }
            }
        }
    ]
).pretty();

/** QUERY QUE DESPLIEGA LA PIZZA QUE MÁS VENTAS HA TENIDO  */

db.orders.aggregate(
    [
        {
            $group: {
                    _id: "$name",
                    ventaTotal: {
                            $sum: {
                                $multiply: ["$price", "$quantity"]
                            }
                        }
                    }
        },
        {
            $sort: {
                ventaTotal: -1,
            }  
        },
        {
            $limit: 1
        } 
    ]   
).pretty();


/** QUERY QUE MUESTRA EL ITEM QUE MÁS SE HA VENDIDO */

db.sales.aggregate(
    [
        {
            $group: {
                _id: "$item",
                ventaTotal: {
                    $sum: {
                        $multiply: ["$price", "$quantity"]
                    }
                }
            }
        },
        {
            $sort: {
                ventaTotal: -1
            }
        },
        {
            $limit: 1
        },
        {
            $project: {
                ventaTotal: 0
            }
        }
    ]
).pretty();

/** QUERY QUE MUESTRA LA PIZZA MÁS CARA */

db.orders.aggregate(
    [
        {
            $group: {
                _id: "$name",
                precioTotal: {
                    $sum: "$price"
                }
            }
        },
        {
            $sort:{
                precioTotal: -1
            }
        },
        {
            $limit: 1
        },
        {
            $project: {
                name: 1
            }
        }
    ]
).pretty();

/** QUERY QUE MUESTRA LA PIZZA QUE TIENE MÁS EN EXISTENCIA */
db.orders.aggregate(
    [
        {
            $group: {
                _id: "$name",
                cantidad: {
                    $sum: "$quantity"
                }
            }
        },
        {
            $sort: {
                cantidad: -1
            }
        },
        {
            $limit: 1
        },
        {
            $project: {
                cantidad: 0
            }
        }
    ]
).pretty();

