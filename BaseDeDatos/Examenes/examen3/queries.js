// 1) QUERY QUE MUESTRA CUANTOS VUELOS HAY DE MÉXICO A VERACRÚZ

db.air_routes.find(
    {
	$and: [{src_airport: "MEX"}, {dst_airport: "VER"}]
    }
).count();

// 5) QUERY QUE MUESTRA CUANTAS LINEAS AÉREAS TIENEN EN TOTAL CANADÁ Y USA

db.air_airlines.find(
    {
	$or: [{country: "United States"}, {country: "Canada"}]
    }
).count();

// 6) QUERY QUE MUESTRA AL TERCER PAÍS CON MÁS AEROLINEAS

db.air_airlines.aggregate(
    [
	{
	    $group:{
		_id: "$country",
		totalAirlines: {
		    $sum: 1
		}
	    }
	},
	{
	    $sort:{
		totalAirlines: -1
	    }
	},
	{
	    $limit: 3
	},
	{
	    $project: {
		totalAirlines: 0
	    }
	}
    ]
).pretty();

// 7) QUERY QUE MUESTRA LA CANTIDAD DE AEROLINEAS DEL PUNTO ANTERIOR

db.air_airlines.aggregate(
    [
	{
	    $group:{
		_id: "$country",
		totalAirlines: {
		    $sum: 1
		}
	    }
	},
	{
	    $sort:{
		totalAirlines: -1
	    }
	},
	{
	    $limit: 3
	}
    ]
).pretty();

// 8) QUERY QUE MUESTRA LA CANTIDAD DE RUTAS QUE VUELA EL AVIÓN 320

db.air_routes.aggregate(
    [
	{
	    $match: {
		airplane: "320"
	    }
	},
	{
	    $group: {
		_id: "$airplane",
		cantidadRutas: {$sum: 1}
	    }
	},
	{
	    $project: {
		_id: 0
	    }
	}
    ]
).pretty();
