#pragma once

#include <set>
#include <deque>

typedef std::set<CPoint> K_POINTS; // Set это множество. Почти тоже что и массив, но все элементы уникальны
typedef std::pair<CPoint, K_POINTS> CLUSTER; // pair это структуру из двух полей
typedef std::deque<CLUSTER> CLUSTERS; // vector это аналог массива

class CPointKMeanClusterizer
{
public:
	CPointKMeanClusterizer(void);
	~CPointKMeanClusterizer(void);
	CPointKMeanClusterizer(size_t num_points, size_t num_clusters, const CRect& border, size_t max_steps); 

	bool IsRun() const;
	CLUSTERS GetClusters() const;

	// Для пошагового выполнения алгоритма
	void Run(size_t num_points, size_t num_clusters, const CRect& border);
	void Step();
	void Stop();
	// Сам генерирует и кластеризует
	void Generate(size_t num_points, size_t num_clusters, const CRect& border, size_t max_steps);
private:
	// Генерирует num_points уникальных точек в пределах прямоугольной границы border
	K_POINTS _GenerateUniquePoints(size_t num_points, const CRect& border);
	// Вытаскивает из points num_clusters точек и делает их центрами кластеров
	K_POINTS _ExtractClusterCenters(size_t num_clusters, K_POINTS& points);
	// Генерит рандомную точку
	CPoint _GetRandomPoint(const CRect& border);
	// Кластеризирует набор точек по набору центров
	CLUSTERS _MakeCluster(const K_POINTS& kmeans, const K_POINTS& points);
	// Центрирует центры кластеров
	K_POINTS _ClusterizeStep(const CLUSTERS& clusters);
private:
	bool _run_mode;
	CLUSTERS _clusters; 
	K_POINTS _points;
};

bool operator<(const CPoint& left, const CPoint& right);
double operator-(const CPoint& left, const CPoint& right);